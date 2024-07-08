//	Библиотека для работы с модулями серии I2C-flash для Arduino: https://iarduino.ru/search/?text=flash
//  Версия: 1.0.4
//  Последнюю версию библиотеки Вы можете скачать по ссылке: https://iarduino.ru/file/558.html
//  Подробное описание функций бибилиотеки доступно по ссылке: https://wiki.iarduino.ru/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел.
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_I2C_Address_h																						//
#define iarduino_I2C_Address_h																						//
																													//
#if defined(ARDUINO) && (ARDUINO >= 100)																			//
#include		<Arduino.h>																							//
#else																												//
#include		<WProgram.h>																						//
#endif																												//
																													//
#include		"iarduino_I2C_Address_I2C.h"																		//	Подключаем библиотеку выбора реализации шины I2C.
																													//
#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega2560__) || defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_RP2040) || defined(RENESAS_CORTEX_M4) // Если подключена библиотека Wire или платы её поддерживают...
#include		<Wire.h>																							//	Разрешаем использовать библиотеку Wire в данной библиотеке.
#endif																												//
#if defined( iarduino_I2C_Software_h )																				//	Если библиотека iarduino_I2C_Software подключена в скетче...
#include		<iarduino_I2C_Software.h>																			//	Разрешаем использовать библиотеку iarduino_I2C_Software в данной библиотеке.
#endif																												//
																													//
#define			DEVICE_I2C_ABSENT		0																			//	Значение возвращаемое функцией getDevice() - Нет модуля с указанным адресом.
#define			DEVICE_I2C_DOUBLE		1																			//	Значение возвращаемое функцией getDevice() - Адрес принадлежит двум и более модулям.
#define			DEVICE_I2C_UNKNOWN		2																			//	Значение возвращаемое функцией getDevice() - Адрес принадлежит модулям не из линейки Flash I2C.
#define			DEVICE_I2C_FLASH		3																			//	Значение возвращаемое функцией getDevice() - Адрес принадлежит модулям линейки Flash I2C.
#define			DEVICE_I2C_FLASH_OLD	4																			//	Значение возвращаемое функцией getDevice() - Адрес принадлежит модулям линейки Flash I2C без поддержки вывода названия и сортировки адреса.
																													//
//	Класс для сортировки устройств Flash I2C:																		//
class iarduino_I2C_SortAddress{																						//
	public:																											//
	/**	Конструктор класса **/																						//
		iarduino_I2C_SortAddress						(void				){ selI2C = new iarduino_I2C_Select; }	//	Конструктор класса														(Параметр:  отсутствует).
	/**	Пользовательские функции **/																				//
		#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__)											//
		void						begin				(TwoWire* i=&Wire	){ selI2C->init(i); selI2C->begin(); }	//	Определяем функцию инициализации модуля									(Параметр:  объект для работы с аппаратной шиной I2C).
		#endif																										//
		#if defined(iarduino_I2C_Software_h)																		//
		void						begin				(SoftTwoWire* i		){ selI2C->init(i); selI2C->begin(); }	//	Определяем функцию инициализации модуля									(Параметр:  объект для работы с программной шиной I2C).
		#endif																										//
		bool						sorting				(uint8_t			);										//	Объявляем  функцию сортировки устройств линейки Flash I2C				(Параметр:  первый назначаемый адрес нового списка).
	private:																										//
	/**	Внутренние переменные **/																					//
		iarduino_I2C_VirtualSelect*	selI2C;																			//	Объявляем  указатель  на  объект полиморфного класса iarduino_I2C_VirtualSelect, но в конструкторе текущего класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C_Select.
		uint8_t						arrF[15];																		//	Объявляем  массив  для хранения флагов наличия устройств Flash I2C.	arrF[0]={0F...08} ,..., arrF[14]={7F...78}.
		uint8_t						arrO[15];																		//	Объявляем  массив  для хранения флагов наличия старых    Flash I2C.	arrO[0]={0F...08} ,..., arrO[14]={7F...78}.
		uint8_t						arrU[15];																		//	Объявляем  массив  для хранения флагов наличия сторонних устройств.	arrU[0]={0F...08} ,..., arrU[14]={7F...78}.
		uint8_t						arrD[15];																		//	Объявляем  массив  для хранения флагов наличия двойных   адресов.	arrD[0]={0F...08} ,..., arrD[14]={7F...78}.
		uint8_t						data[15];																		//	Объявляем  массив  для хранения получаемых/передаваемых данных.
		uint8_t						valAddr				=	0;														//	Определяем переменную для хранения адреса модуля на шине I2C.
	/**	Внутренние функции **/																						//
		bool						_changeAddress		(uint8_t					);								//	Объявляем  функцию смены адреса модуля valAddr на указанный				(Параметр:  новый адрес модуля).
		uint8_t						_checkDevice		(void						);								//	Объявляем  функцию проверки типа устройства valAddr						(Параметр:	отсутствует).
		bool						_readBytes			(uint8_t, uint8_t			);								//	Объявляем  функцию чтения данных из устройства valAddr в  массив  data	(Параметры: номер первого регистра, количество байт).
		bool						_writeBytes			(uint8_t, uint8_t, uint8_t=0);								//	Объявляем  функцию записи данных в  устройство valAddr из массива data	(Параметры: номер первого регистра, количество байт, номер первого элемента массива data).
		bool						_getBit				(uint8_t* arr, uint8_t adr	);								//	Объявляем  функцию чтения     флага наличия адреса adr в массиве arr.
		void						_setBit				(uint8_t* arr, uint8_t adr	);								//	Объявляем  функцию установки  флага наличия адреса adr в массиве arr.
		void						_delBit				(uint8_t* arr, uint8_t adr	);								//	Объявляем  функцию сброса     флага наличия адреса adr в массиве arr.
		uint8_t						_getSum				(uint8_t* arr				);								//  Объявляем  функцию получения  количества флагов        в массиве arr.
		void						_fillArray			(void						);								//  Объявляем  функцию заполнения массивов arrF, arrO, arrU и arrD.
};																													//
																													//
//	Класс для работы с модулями:																					//
class iarduino_I2C_Address{																							//
	public:																											//
	/**	Конструктор класса **/																						//
		iarduino_I2C_Address							(uint8_t address=0	){ if(address>0x7F){ address>>=1;	}	//	Конструктор класса														(Параметр: адрес модуля на шине I2C, если не указан (=0), то адрес будет определён).
									valAddrTemp			=	address;												//	Сохраняем переданный адрес модуля.
			static uint8_t			objSum				=	0;														//	Определяем переменную для хранения количества созданных объектов класса.
									valObjNum			=	objSum++;												//	Определяем номер созданного объекта класса.
									selI2C				=	new iarduino_I2C_Select;								//	Переопределяем указатель selI2C на объект производного класса iarduino_I2C_Select.
		}																											//
	/**	Пользовательские функции **/																				//
		#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__)											//
		bool						begin				(TwoWire* i=&Wire	){ selI2C->init(i); return _begin(); }	//	Определяем функцию инициализации модуля								(Параметр:  объект для работы с аппаратной шиной I2C).
		#endif																										//
		#if defined(iarduino_I2C_Software_h)																		//
		bool						begin				(SoftTwoWire* i		){ selI2C->init(i); return _begin(); }	//	Определяем функцию инициализации модуля								(Параметр:  объект для работы с программной шиной I2C).
		#endif																										//
		bool						reset				(void				);										//	Объявляем  функцию перезагрузки модуля									(Параметр:  отсутствует).
		bool						changeAddress		(uint8_t			);										//	Объявляем  функцию смены адреса модуля на шине I2C						(Параметр:  новый адрес модуля).
		uint8_t						getAddress			(void				){ return valAddr;					}	//	Определяем функцию возвращающую текущий адрес модуля на шине I2C		(Параметр:  отсутствует).
		uint8_t						getVersion			(void				){ return valVers;					}	//	Определяем функцию возвращающую текущую версию прошивки модуля			(Параметр:  отсутствует).
		uint8_t						getModel			(void				){ return valModel;					}	//	Определяем функцию возвращающую номер модели модуля						(Параметр:  отсутствует).
		uint8_t						getDevice			(void				){ return valDevice;				}	//	Определяем функцию возвращающую тип модуля: DEVICE_I2C_...				(Параметр:  отсутствует).
		String						getName				(void				);										//	Объявляем  функцию возвращающую название модуля							(Параметр:  отсутствует).
		bool						getPullI2C			(void				);										//	Объявляем  функцию возвращающую флаг наличия подтяжки шины I2C			(Параметр:  отсутствует).
		bool						setPullI2C			(bool=true			);										//	Объявляем  функцию установки    подтяжки шины I2C						(Параметр:  флаг подтяжки).
		bool						operator =			(uint8_t adr		){ return changeAddress(adr);		}	//	Определяем функцию смены адреса модуля на шине I2C						(Параметр:  новый адрес модуля).
									operator uint8_t	(					){ return valAddr;					}	//	Определяем функцию возвращающую текущий адрес модуля на шине I2C		(Параметр:  отсутствует).
	private:																										//
	/**	Внутренние переменные **/																					//
		iarduino_I2C_VirtualSelect* selI2C;																			//	Объявляем  указатель  на  объект полиморфного класса iarduino_I2C_VirtualSelect, но в конструкторе текущего класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C_Select.
		uint8_t						valAddrTemp			=	0;														//	Определяем переменную для хранения адреса модуля на шине I2C который был указан, но не был проверен.
		uint8_t						valVers				=	0;														//	Определяем переменную для хранения версии прошивки модуля.
		uint8_t						valModel			=	0;														//	Определяем переменную для хранения номера модели модуля.
		uint8_t						valDevice			=	DEVICE_I2C_ABSENT;										//	Определяем переменную для хранения типа модуля: DEVICE_I2C_ABSENT / DEVICE_I2C_DOUBLE / DEVICE_I2C_UNKNOWN / DEVICE_I2C_FLASH.
		uint8_t						valObjNum;																		//	Объявляем  переменную для хранения номера созданного объекта класса.
		uint8_t						valAddr				=	0;														//	Определяем переменную для хранения адреса модуля на шине I2C.
		uint8_t						data[2];																		//	Объявляем  массив     для хранения получаемых/передаваемых данных.
	/**	Внутренние функции **/																						//
		bool						_begin				(void						);								//	Объявляем  функцию начала работы с модулем								(Параметр:  отсутствует).
		uint8_t						_checkDevice		(void						);								//	Объявляем  функцию проверки типа устройства valAddr						(Параметр:	отсутствует).
		bool						_readBytes			(uint8_t, uint8_t			);								//	Объявляем  функцию чтения данных из устройства valAddr в  массив  data	(Параметры: номер первого регистра, количество байт).
		bool						_writeBytes			(uint8_t, uint8_t, uint8_t=0);								//	Объявляем  функцию записи данных в  устройство valAddr из массива data	(Параметры: номер первого регистра, количество байт, номер первого элемента массива data).
};																													//
																													//
#endif																												//