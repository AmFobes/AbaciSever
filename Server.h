#pragma once
#include "gui/MainWindow.h"
#include <bitset>
#include <QApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>

/* This class creates a thread for each socket */
class ThreadedAbaciServer : public QObject{
class gdh {
	public:
		double highestPrime;
		double highestDispatched;
		double dispatchCount; // Dispatch count per client
	};
public:
	QObject* parentObject;
private:
	enum ServerPacketType {
		SHUTTINGDOWN = 0XF0,
		AUTHRESP = 0XF1,
		AVAILABLEREQUEST= 0XF2,
		RESETPASSWORD = 0XF3,
		CLIENTID = 0XF4,
		CLIENTUSERNAME = 0XF5,
		CLIENTWORKCOMPLETED = 0XF6,
		CLIENTCPUINFO = 0XF7,
		CLIENTCPUCOUNT = 0XF8,
		CLIENTPLATFORM = 0XF9,
		DATABASELESS = 0XFA,
		NOTAUTHED = 0XFB,
		// UNDEFINED = 0XFC,
		// UNDEFINED = 0XFD,
		SERVERONLINE = 0XFE,
		HEARTBEAT = 0XFF

	};
	enum class ClientPacketType {
		DISCONNECTING = 0X00,
		AUTHREQ = 0X01,
		WORKREQ = 0X02,
		RESETPASSWORD = 0X03,
		REQCLIENTDETAILS = 0X04,
		SETCLIENTUSERNAME = 0X05,
		SETCLIENTCPU = 0X06,
		SETCLIENTPLATFOM = 0X07,
		REQRESULT = 0X08,
		CLIENTDELETEME = 0X09,
		REQCLIENTCOUNT = 0X0A,
		CLIENTWORKRESULT = 0X0B,
		// UNDEFINED = 0X0C,
		// UNDEFINED = 0X0D,
		// UNDEFINED = 0X0E,
		HEARTBEAT = 0X0F
	};
	enum PacketSuccess {
		FAILURE = 0X0,
		SUCCESS = 0X01,
		UNKNOWN = 0X02,
		ERROR = 0X03,
		CRITICAL = 0X04
	};
	QTcpServer _server;
	gdh GlobalDispatchHelper;
public:
	class AbaciClientInstance : public QObject {
	public:
		std::unique_ptr<QTcpSocket> clSocket;
	private:	
		ThreadedAbaciServer *serverInstance; // The ThreadedAbaciServer instance that is managing us, allows us to invoke the server thread
		QString generateDispatchRange() {
			QString range = QString::number(serverInstance->GlobalDispatchHelper.highestDispatched);
			serverInstance->GlobalDispatchHelper.highestDispatched += serverInstance->GlobalDispatchHelper.dispatchCount;
			
			range += ":";
			range += QString::number(serverInstance->GlobalDispatchHelper.highestDispatched);
			return range;
		}
		QByteArray GeneratePacket(ServerPacketType packetType,PacketSuccess pSuccess = UNKNOWN,QByteArray data = nullptr) {
			
			QByteArray packetData;

			packetData.append(0xAB); // Abaci Signature

			packetData.append(packetType);
			packetData.append(pSuccess);
			
			if (data != nullptr) {
				uint16_t size = data.size();
				uint8_t lsize = size; // Implicit cast, drops the high bits from bytes and only fetches the low bits
				uint8_t hsize = size >> 8; // Shift the size, 8 bits to the right to get the high bits
										   // The implicit cast to 16 bits -> 8 bits will ignore the high bits
				packetData.append(hsize);
				packetData.append(lsize);
				packetData.append(data);
			}
			else {
				packetData.append(2,(int8_t)0);		
			}

			packetData.append(0xAB); // Abaci signature

			return packetData;
		}
	public:
		/* Client details */
		int clID = 0;
		QString clUsername;
		int clWorkCompleted = 0;
		QString clProcessorInfo;
		int clProcessorCoreCount = 0;
		QString clPlatform;
		bool clAuthed = false;
		
		AbaciClientInstance(QTcpSocket* connectedClient, ThreadedAbaciServer* parent) : clSocket(connectedClient), serverInstance(parent) {
			connect(clSocket.get(), &QTcpSocket::disconnected, this, &AbaciClientInstance::onSocketDisconnected);
			connect(clSocket.get(), &QTcpSocket::readyRead, this, &AbaciClientInstance::onSocketReadyRead, Qt::DirectConnection);
		}
		void clientConnected(QString username) {
			serverInstance->parentMainWindow->clientConnected(username);
		}
		void clientDisconnected(QString username) {
			serverInstance->parentMainWindow->clientDisconnected(username);
		}
		void kickClient() {
			clSocket->write(GeneratePacket(SHUTTINGDOWN, SUCCESS, "You've been kicked"));
			clSocket->flush();
		}
	private slots:
		void onSocketDisconnected() {
			this->clientDisconnected(clUsername);
			this->disconnectSocket();
		}
		
		void disconnectSocket() {
			clSocket->write(GeneratePacket(SHUTTINGDOWN, SUCCESS));
			clSocket->flush();
			clSocket->close();
		}
		void onSocketReadyRead() {
			read:
			QByteArray socketMessage;
			
			uint8_t signatureByte;
			clSocket->read((char*)&signatureByte, sizeof(uint8_t));
			if (signatureByte == (uint8_t)0xAB) {
				
				uint8_t appFunctionByte;
			buffernotempty:
				clSocket->read((char*)&appFunctionByte, sizeof(uint8_t));
				if (appFunctionByte == (uint8_t)0xab) {
					goto buffernotempty;
				}
				std::bitset<8> appFunctionBitset(appFunctionByte);
				
				uint8_t successByte;
				clSocket->read((char*)&successByte, sizeof(uint8_t));

				uint16_t resultSizeBytes;
				uint8_t hResultSize,lResultSize;
				clSocket->read((char*)&hResultSize, sizeof(uint8_t));
				clSocket->read((char*)&lResultSize, sizeof(uint8_t));
				resultSizeBytes = hResultSize << 8 | lResultSize; // Move the high bits to the right position and OR the low bits
																  // This forms our full result amount
				if (appFunctionBitset.test(7)) {
					// Server app
				}
				else {
					// Client app
					appFunctionBitset &= 0x0F; // Clear the top half of the byte
					// Look at the abaci protocol spreadsheet to view the list of hex codes and their meanings
					switch ((uint8_t)appFunctionBitset.to_ulong()) {
					case 0x00:
						// Client Disconnect
						this->onSocketDisconnected();
						break;
					case 0x01:
						// Client Authentication request
						// We expect the username and password to be in the result
						if (resultSizeBytes <= 0) {
							clSocket->write(GeneratePacket(AUTHRESP, FAILURE, "Empty request"));
						}
						else {
							QByteArray rawUserPass = clSocket->read(resultSizeBytes);
							QString userPass = QString::fromStdString(rawUserPass.toStdString());
							if (!userPass.contains(':')) {
								clSocket->write(GeneratePacket(AUTHRESP, FAILURE, "Invalid request"));
							}
							else {
								QStringList userPassSplit = userPass.split(':');
								bool result;

								QMetaObject::invokeMethod(serverInstance->parentObject, "tryAuth",
									Qt::DirectConnection,
									Q_RETURN_ARG(bool, result),
									Q_ARG(QString, userPassSplit[0]),
									Q_ARG(QString, userPassSplit[1]));

								clUsername = userPassSplit[0];

								if (result) {
									clSocket->write(GeneratePacket(AUTHRESP, SUCCESS));

									QMetaObject::invokeMethod(serverInstance->parentObject, "getClientID",
										Qt::DirectConnection,
										Q_RETURN_ARG(int, clID),
										Q_ARG(QString, clUsername)); // If the authentication was successful, get the client ID
									clAuthed = true;
									clientConnected(clUsername);
								}
								else {
									clSocket->write(GeneratePacket(AUTHRESP, FAILURE, "Authentication failed"));
								}
							}
						}
						break;
					case 0x02:
						// Client work request
						if (successByte == SUCCESS) {
							QString range = generateDispatchRange();
							clSocket->write(GeneratePacket(AVAILABLEREQUEST, SUCCESS, QByteArray::fromStdString(range.toStdString())));
							clSocket->flush();
						}
						break;
					case 0x03:
						// Client asking to reset their password
						if (!clAuthed)
							clSocket->write(GeneratePacket(NOTAUTHED));
						else if (resultSizeBytes <= 0)
							clSocket->write(GeneratePacket(RESETPASSWORD, FAILURE, "Empty request"));
						else {
							QByteArray newRawPassword = clSocket->read(resultSizeBytes);

							QString newPassword = QString::fromStdString(newRawPassword.toStdString());
							bool result;
							QMetaObject::invokeMethod(serverInstance->parentObject, "resetPassword",
								Qt::DirectConnection,
								Q_RETURN_ARG(bool, result),
								Q_ARG(QString, clUsername),
								Q_ARG(QString, newPassword));
							if (result) {
								clSocket->write(GeneratePacket(RESETPASSWORD, SUCCESS));
							}
							else {
								clSocket->write(GeneratePacket(RESETPASSWORD, FAILURE));
							}
						}
						break;
					case 0x04:
						// Request client details
						if (!clAuthed)
							clSocket->write(GeneratePacket(NOTAUTHED));
						else {
							if (clID == -1)
								QMetaObject::invokeMethod(serverInstance->parentObject, "getClientID",
									Qt::DirectConnection,
									Q_RETURN_ARG(int, clID),
									Q_ARG(QString, clUsername));
							if (clID == -1)
								clSocket->write(GeneratePacket(CLIENTID, FAILURE));
							else {
								clSocket->write(GeneratePacket(CLIENTID, SUCCESS, QByteArray::number(clID)));
							}
							clSocket->flush();
							if (clUsername.isEmpty()) {
								clSocket->write(GeneratePacket(CLIENTUSERNAME, CRITICAL)); // We use the username in our invoke functions 
																						  // If the username is empty, that's really bad
								clSocket->disconnect();
								return;
							}
							else {
								clSocket->write(GeneratePacket(CLIENTUSERNAME, SUCCESS, clUsername.toStdString().c_str()));
							}
							clSocket->flush();
							if (clWorkCompleted == -1 || clWorkCompleted == 0)
								QMetaObject::invokeMethod(serverInstance->parentObject, "getWorkCompleted",
									Qt::DirectConnection,
									Q_RETURN_ARG(int, clWorkCompleted),
									Q_ARG(QString, clUsername));
							if (clWorkCompleted == -1)
								clSocket->write(GeneratePacket(CLIENTWORKCOMPLETED, FAILURE));
							else
								clSocket->write(GeneratePacket(CLIENTWORKCOMPLETED, SUCCESS, QByteArray::number(clWorkCompleted)));

							clSocket->flush();
							if (clProcessorCoreCount == -1 || clProcessorCoreCount == 0)
								QMetaObject::invokeMethod(serverInstance->parentObject, "getProcessorCoreCount",
									Qt::DirectConnection,
									Q_RETURN_ARG(int, clProcessorCoreCount),
									Q_ARG(QString, clUsername));

							if (clProcessorCoreCount == -1 || clProcessorCoreCount == 0)
								clSocket->write(GeneratePacket(CLIENTCPUCOUNT, FAILURE));
							else
								clSocket->write(GeneratePacket(CLIENTCPUCOUNT, SUCCESS, QByteArray::number(clProcessorCoreCount)));

							clSocket->flush();
							if (clProcessorInfo == "")
								QMetaObject::invokeMethod(serverInstance->parentObject, "getProcessorInfo",
									Qt::DirectConnection,
									Q_RETURN_ARG(QString, clProcessorInfo),
									Q_ARG(QString, clUsername));

							clSocket->write(GeneratePacket(CLIENTCPUINFO, SUCCESS, clProcessorInfo.toStdString().c_str()));

							clSocket->flush();
							if (clPlatform == "")
								QMetaObject::invokeMethod(serverInstance->parentObject, "getPlatform",
									Qt::DirectConnection,
									Q_RETURN_ARG(QString, clPlatform),
									Q_ARG(QString, clUsername));

							clSocket->write(GeneratePacket(CLIENTPLATFORM, SUCCESS, clPlatform.toStdString().c_str()));
							clSocket->flush();
						}
						break;
					case 0x05:
						// Set Client Username
						if (!clAuthed) {
							clSocket->write(GeneratePacket(NOTAUTHED, SUCCESS));
							clSocket->flush();
						}
						if (resultSizeBytes <= 0) {
							clSocket->write(GeneratePacket(CLIENTUSERNAME, FAILURE, "Empty request"));
							clSocket->flush();
						}
						else {

							QByteArray newUsernameRaw = clSocket->read(resultSizeBytes);
							QString newUsername = QString::fromStdString(newUsernameRaw.toStdString());

							bool userExists;
							QMetaObject::invokeMethod(serverInstance->parentObject, "checkUserExists",
								Qt::DirectConnection,
								Q_RETURN_ARG(bool, userExists),
								Q_ARG(QString, newUsername));

							if (userExists) {
								clSocket->write(GeneratePacket(CLIENTUSERNAME, FAILURE, "Username already in use"));
								clSocket->flush();
							}
							else {
								bool result;
								QMetaObject::invokeMethod(serverInstance->parentObject, "setClientUsername",
									Qt::DirectConnection,
									Q_RETURN_ARG(bool, result),
									Q_ARG(QString, clUsername),
									Q_ARG(QString, newUsername));

								if (!result) {
									clSocket->write(GeneratePacket(CLIENTUSERNAME, FAILURE));
									clSocket->flush();
								}
								else {
									clUsername = newUsername;
									clSocket->write(GeneratePacket(CLIENTUSERNAME, SUCCESS, clUsername.toStdString().c_str()));
									clSocket->flush();
								}

							}
						}

						break;
					case 0x06:
						if (!clAuthed) {
							clSocket->write(GeneratePacket(NOTAUTHED, SUCCESS));
							clSocket->flush();
						}
						else if (resultSizeBytes <= 0) {
							clSocket->write(GeneratePacket(CLIENTCPUINFO, FAILURE, "Empty request"));
							clSocket->flush();
						}
						else {
							QByteArray newProcessorInfoRaw = clSocket->read(resultSizeBytes);
							QString newProcessorInfo = QString::fromStdString(newProcessorInfoRaw.toStdString());
							bool result;
							QMetaObject::invokeMethod(serverInstance->parentObject, "setClientProcessorInfo",
								Qt::DirectConnection,
								Q_RETURN_ARG(bool, result),
								Q_ARG(QString, clUsername),
								Q_ARG(QString, newProcessorInfo));

							if (!result) {
								clSocket->write(GeneratePacket(CLIENTCPUINFO, FAILURE));
								clSocket->flush();
							}
							else {
								clProcessorInfo = newProcessorInfo;
								clSocket->write(GeneratePacket(CLIENTCPUINFO, SUCCESS, clProcessorInfo.toStdString().c_str()));
								clSocket->flush();
							}
						}
						break;
					case 0x07:
						if (!clAuthed) {
							clSocket->write(GeneratePacket(NOTAUTHED, SUCCESS));
							clSocket->flush();
						}
						else if (resultSizeBytes <= 0) {
							clSocket->write(GeneratePacket(CLIENTPLATFORM, FAILURE, "Empty request"));
							clSocket->flush();
						}
						else {
							QByteArray newPlatformRAW = clSocket->read(resultSizeBytes);
							QString newPlatform = QString::fromStdString(newPlatformRAW.toStdString());
							bool result;
							QMetaObject::invokeMethod(serverInstance->parentObject, "setClientPlatform",
								Qt::DirectConnection,
								Q_RETURN_ARG(bool, result),
								Q_ARG(QString, clUsername),
								Q_ARG(QString, newPlatform));

							if (!result) {
								clSocket->write(GeneratePacket(CLIENTPLATFORM, FAILURE));
								clSocket->flush();
							}
							else {
								clPlatform = newPlatform;
								clSocket->write(GeneratePacket(CLIENTPLATFORM, SUCCESS, clPlatform.toStdString().c_str()));
								clSocket->flush();
							}
						}
						break;
					case 0x08:
					
								break;
					case 0x09:
						if (!clAuthed) {
							clSocket->write(GeneratePacket(NOTAUTHED, SUCCESS));
							clSocket->flush();
						}
						else {
							bool result;
							QMetaObject::invokeMethod(serverInstance->parentObject, "deleteClientOnClientRequest",
								Qt::DirectConnection,
								Q_RETURN_ARG(bool, result),
								Q_ARG(QString, clUsername));

							if (!result) {
								clSocket->write(GeneratePacket(AUTHRESP, SUCCESS, "Client not deleted"));
								clSocket->flush();
							}
							else {
								clSocket->write(GeneratePacket(NOTAUTHED, SUCCESS)); // Client has been deleted and is no longer authed
								clSocket->flush();
								clAuthed = false;
							}
						}
						break;
					case 0x0A:	

						break;
					case 0x0B:
						if (!clAuthed) {
							clSocket->write(GeneratePacket(NOTAUTHED, SUCCESS));
							clSocket->flush();
						}
						else {
							if (resultSizeBytes <= 0) {
								clSocket->write(GeneratePacket(CLIENTWORKCOMPLETED, FAILURE, "Empty request"));
								clSocket->flush();
							}
							else {
								double primeCount = 0;
								QByteArray primeSaved;
								long bytesRead = 0;
								while (true) {
									
									QByteArray prime;
									prime.append(clSocket->read(1));
									bytesRead++;
									if (prime.toStdString().c_str()[0] == ':'){
										primeCount = primeSaved.toDouble();
										break;
									}
									else {
										primeSaved.append(prime);
										prime.clear();
									}
								}
									
								if (primeCount >= 1) {

									std::vector<double> primes;
									QByteArray prime;
									for (int count = 0; count < primeCount; count++) {
										QByteArray inByte;
										inByte = clSocket->read(1);
										//QThread::msleep(5); // Add read delay, otherwise it doesn't detect stuff, I'm unsure as to why
										if (inByte.toStdString().c_str()[0] == ':') {
											primes.push_back(prime.toDouble());
											prime.clear();
										}
										else {
											prime.append(inByte);
										}
									
									}
									QMetaObject::invokeMethod(serverInstance->parentObject, "addResult",
										Q_ARG(std::vector<double>, primes),
										Q_ARG(int, clID));
									clSocket->write(GeneratePacket(AVAILABLEREQUEST, UNKNOWN));
									clSocket->read(resultSizeBytes - bytesRead); // Read the remaining bytes in the payload
								}
							}
						}
					case 0x0C:
					case 0x0D:
					case 0x0E:
						// Unimplemented
						break;
					case 0x0F:

						break;
					}
				}
				clSocket->read(1); // Read ending signature
				if (clSocket->bytesAvailable() >= 6)
					goto read;
			}
			else {
			clSocket->readAll(); // Clear input buffer
			}
		}
	};

public:
	std::vector<AbaciClientInstance*> ConnectedClients;
	MainWindow* parentMainWindow;
	ThreadedAbaciServer(QObject *parent) {
		this->parentObject = parent;
		_server.listen(QHostAddress::Any, 5123);
		connect(&_server, &QTcpServer::newConnection, this, &ThreadedAbaciServer::newConnection);
		parentMainWindow = qobject_cast<MainWindow*>(parent);
		connect(parentMainWindow, &MainWindow::gdhReady, this, &ThreadedAbaciServer::setGDH);
	
		if (_server.isListening()) {
			std::cout << "Server is listening" << std::endl;
		}
	}
public slots:
	void socketDisconnectedCallback(AbaciClientInstance *clientInstance) { // Gets invoked by the socket thread, allows us to remove the client thread and resources
		clientInstance->deleteLater(); // Delete the client instance
		ConnectedClients.erase(std::find(ConnectedClients.begin(),ConnectedClients.end(),clientInstance)); // Remove the client instance from the client list
	}
	void newConnection() {
		ConnectedClients.push_back(new AbaciClientInstance(_server.nextPendingConnection(),this));
	}
	void shutdown() {
		for (auto& clientInstance : ConnectedClients) {
			QMetaObject::invokeMethod(clientInstance, "disconnectSocket",Qt::BlockingQueuedConnection);
		}
		QThread::currentThread()->quit();
	}
	void setGDH(double prime) {	
		GlobalDispatchHelper.dispatchCount = 10000;
		GlobalDispatchHelper.highestDispatched = prime;
		GlobalDispatchHelper.highestPrime = prime;
	}
	void kickClientRequest(const QString& username) {
		for (auto& clientInstance : ConnectedClients) {
			if (clientInstance->clUsername == username) 
				clientInstance->kickClient();
			

		}
	}
};
