#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtSerialPort/QSerialPort>
# include <QtSerialPort/QSerialPortInfo>
#include <QTcpSocket>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothSocket>
#include <QHostAddress>
#include <QDebug>
#include<QString>
#include<QByteArray>
#include<QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    // Find the first available serial port
        QString portName;
        foreach (const QSerialPortInfo& port, QSerialPortInfo::availablePorts())
        {
            if(port.portName() != NULL && port.portName() != ""){
                qDebug() << "serial port Name COM3" << port.portName();
                portName = port.portName();
                break;
            }

        }

// Open the serial port for writing
        QSerialPort serialPort(portName);
        serialPort.setBaudRate(QSerialPort::Baud9600);
        serialPort.setParity(QSerialPort::NoParity);
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setStopBits(QSerialPort::OneStop);

        if (!serialPort.open(QIODevice::WriteOnly))
        {
            qDebug() << "Failed to open serial port " << portName;
        }else{

        // Send ESC/POS commands to the printer
        QByteArray data;
        data.append("\x1B\x40"); // Initialize printer
        data.append("\x1B\x61\x01"); // Center alignment
        data.append("Hello, world!\n"); // Print text
        data.append("\x1D\x68\x64"); // Set barcode height
        data.append("\x1D\x6B\x04\x31\x32\x33\x34"); // Print barcode
        data.append("\n\x1D\x56\x01\x1d\x56\x00"); // Cut paper
        data.append("\x1d\x56\x00");

        // Load the image file and convert it to the appropriate format
            QImage image(":/mm.png"); // Replace with the path to your image file
            QByteArray imageData = convertImageToPrinterFormat(image); // Replace with your function to convert the image to the appropriate format

            // Send the image to the printer
            const QByteArray imageCommand = "\x1B\x40" // Reset the printer
                                             "\x1B\x33\x00" // Set line spacing to 0
                                             "\x1B\x32" // Set default line spacing
                                             "\x1B\x38\x38\x37\x57\x02" // Select the image command
                                             + QByteArray::number(imageData.size() / 1024) // High byte of the image size
                                             + QByteArray::number(imageData.size() % 1024) // Low byte of the image size
                                             + imageData; // The image data

        serialPort.write(data);
        serialPort.flush();
        serialPort.close();
        }
}


void MainWindow::on_pushButton_2_clicked()
{
    // Create a TCP socket
        QTcpSocket socket;

        // Connect to the printer using its IP address and port
        socket.connectToHost(QHostAddress("192.168.8.200"), 9100);

        // Wait for the connection to be established
        if (!socket.waitForConnected(7000)) {
            // Error: connection failed
            qDebug() << "77 Error: connection failed";
            return;
        }

        // Send each row as a print command with a line feed
        QStringList rows;
        rows.append("Row 1");
        rows.append("Row 2");
        rows.append("Row 3");

        foreach (const QString& row, rows) {
            // Send a print command to the printer
            QString command = QString("%1%2").arg(row).arg(QChar(0x0A)); // Add a line feed to the end of the row
            socket.write(command.toUtf8());

            // Wait for the command to be sent
            if (!socket.waitForBytesWritten(3000)) {
                // Error: failed to send command
                 qDebug() << "95 Error: connection failed";
                return;
            }
        }

        // Close the connection
        socket.disconnectFromHost();
}


void MainWindow::on_pushButton_3_clicked()
{
    // Create a discovery agent to find Bluetooth devices
        QBluetoothDeviceDiscoveryAgent agent;
        agent.setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);

        // Connect to the printer when it is discovered
        QObject::connect(&agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, [=](const QBluetoothDeviceInfo &device){
            if (device.name() == "CN810-UWB") {
                // Create a socket and connect to the printer
                QBluetoothSocket socket(QBluetoothServiceInfo::RfcommProtocol);
                socket.connectToService(device.address(), QBluetoothUuid(QBluetoothUuid::SerialPort));
                if (socket.state() == QBluetoothSocket::ConnectedState) {
                    // Send data to the printer
                    socket.write("Hello, world!");
//                    socket.flush();
                    socket.close();
                }
            }else{
                 qDebug() <<device.name()<< "95 Error: connection failed";
            }
        });

        // Start the discovery process
        agent.start();
}

QByteArray MainWindow::convertImageToPrinterFormat(const QImage &image)
{
    // Resize the image to the appropriate size for your printer
       const int width = 384; // Replace with the width of your printer
       const int height = image.height() * width / image.width();
       const QImage resizedImage = image.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

       // Convert the image to black and white
       const QImage bwImage = resizedImage.convertToFormat(QImage::Format_Grayscale8);

       // Convert the image to a bitmap format
       QByteArray bitmapData;
       for (int y = 0; y < bwImage.height(); y += 8) {
           for (int x = 0; x < bwImage.width(); ++x) {
               char byte = 0;
               for (int i = 0; i < 8 && y + i < bwImage.height(); ++i) {
                   const bool isBlack = bwImage.pixel(x, y + i) == Qt::color1;
                   byte |= static_cast<char>(isBlack) << i;
               }
               bitmapData.append(byte);
           }
       }

       return bitmapData;
}
