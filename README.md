Консоль облака: https://console.yandex.cloud/folders/b1g11ldc88cj7vpl7tba

# Словарь понятий

**Устройство**  — экземпляр физического устройства, например, датчика температуры, представленный в сервисе в виде имени устройства и его сертификата.
\
**Реестр** — набор устройств, логически связанных между собой.
\
**Брокер** — виртуальный MQTT-сервер, позволяющий MQTT-клиентам обмениваться сообщениями в изолированном пространстве топиков.
\
**MQTT-сервер** — это центральный узел для обмена MQTT-сообщениями между устройствами и реестрами.
\
**MQTT-клиенты** — это устройства, реестры и клиенты брокера, которые обмениваются сообщениями с данными или командами. Клиентом может быть, например, SCADA-система.
\
**Топик** — канал отправки и получения сообщений между устройствами, реестрами и клиентами брокера.

# Шаги по развёртыванию IoT-инфраструктуры

## Первичные действия
1. Создать платёжный аккаунт - https://yandex.cloud/ru/docs/iot-core/quickstart#before-you-begin

2. Получить личный токен: https://oauth.yandex.ru/authorize?response_type=token&client_id=1a6990aa636648e9b2ef855fa7bec2fb

3. Настроить CLI - https://yandex.cloud/ru/docs/cli/quickstart#install

4. Сгенерировать сертификат реестра усройств
```bash
openssl req -x509 \
-newkey rsa:4096 \
  -keyout registries/private-key.pem \
  -out registries/cert.pem \
  -nodes \
  -days 365 \
  -subj '/CN=localhost'
```

5. Создать  реестр, где будут все устройства
```bash
yc iot registry create --name "water-meter-telemetry" --description "Test registry for water meter MQTT sensors"
```

6. Добавить ранее созданный сертификат для нового реестра
```bash
yc iot registry certificate add \
   --registry-name "water-meter-telemetry" \
   --certificate-file registries/cert.pem
```

7. Получить ID реестра
```bash
yc iot registry get --name "water-meter-telemetry" | grep -w "id:" | awk -F " " '{print $2}'
```
Итоговые данные по созданному реестру (записать их в прошивку):
```json
"name": "water-meter-telemetry"
"id": "are6phis3t903qjfrje3"
```

## Добавление нового устройства в реестр (повторить для каждого нового устройства)
7. Сгенерировать сертификат устройства
```bash
openssl req -x509 \
-newkey rsa:4096 \
  -keyout devices/private-key.pem \
  -out devices/cert.pem \
  -nodes \
  -days 365 \
  -subj '/CN=localhost'
```

8. Создать новое устройство
```bash
yc iot device create \
  --registry-name "water-meter-telemetry" \
  --name "sim7080-module-test"
```

9. Добавить сертификат устройству
```bash
yc iot device certificate add \
  --device-name "sim7080-module-test" \
  --certificate-file devices/cert.pem
```

10. Получить device-id
```bash
yc iot device get --name sim7080-module-test | grep -w "id:" | awk -F " " '{print $2}'
```
Физическое устройство (счётчик) представлен в сервисе Yandex Core в виде **имени устройства и его сертификата** (публичная часть). Топики устройсва существуют сразу при создании устройства. Чтобы в них что-то писать с реального физического устройства небходимо в прошивке знать id, который создаётся яндексом.

Итог после генерации девайса:
```json
"name": "sim7080-module-test"
"id": "areg0sn8p3rf0mkrc0q5"
```

# Кто и какие топики читает
```
$registries/are6phis3t903qjfrje3/events
```
Это топик созданного реестра. **В него пишут все устройства**, авторизуясь по своим сертификатам. SCADA-система подписывается на этот же самый топик и парсит полученные сообщения.

### Локально от имени устройсва (по сертификату) записать тестовые данные в топик реестра:
```bash
yc iot mqtt publish \
  --cert devices/cert.pem \
  --key devices/private-key.pem \
  --topic '$registries/are6phis3t903qjfrje3/events' \
  --message 'Test data' \
  --qos 1
```

### Локально прочитать тестовые данные, развернув node-red:
1) Запустить node-red в консоли
2) Подписаться на `$registries/are6phis3t903qjfrje3/events`
3) Печатать все присланные сообщения

mqtt.cloud.yandex.net
8883

# Настройка SIM7080
```bash
AT+CREBOOT
AT
AT+CSCLK=0 # Disable entering sleep mode
AT+CPIN?   # Is SIM ready?
AT+CFUN=0  # Disable RF
AT+CNMP=2  # GSM or LTE is defined automatically
AT+CMNB=2  # NB-Iot

# Connect to NB-IOT
AT+CGDCONT=1,"IP","iot" # PDP context (шлюз до операторской сети)
AT+CNCFG=0,1,"iot"      # Set the APN manually. Some operators need to set APN first when registering the network.
AT+CFUN=1               # Full functionality
AT+CNACT=0,1            # Activate network bearer

# Get params
AT+CGDCONT?  # PDP context
AT+CEREG?    # Network Registration Status
AT+COPS?
AT+CCLK?     # Precize time
AT+CGPADDR=1 # Get local IP

# Upload device and server certificates 
AT+CFSTERM # Free the Flash Buffer Allocated by CFSINIT (if was)

# rootCA
AT+CFSINIT
AT+CFSWFILE=3,"rootCA.crt",0,1800,10000
<скопировать и отправить данные из файла сертификата ЯНДЕКСА>
AT+CFSTERM

# Device cert
AT+CFSINIT
AT+CFSWFILE=3,"deviceCert.pem",0,1776,10000
<скопировать и отправить данные из файла сертификата ДЕВАЙСА>
AT+CFSTERM

# Device private key
AT+CFSINIT
AT+CFSWFILE=3,"devicePrivateKey.pem",0,3220,10000
<скопировать и отправить данные из файла ПРИВАТНОГО КЛЮЧА ДЕВАЙСА>
AT+CFSTERM

# Configure SSL parameters of a context identifier
AT+SMDISC
AT+CSSLCFG="SNI",0,"mqtt.cloud.yandex.net"

# Set MQTT Parameter
AT+SMCONF="URL","mqtt.cloud.yandex.net",8883
AT+SMCONF="CLIENTID",0
AT+SMCONF="KEEPTIME",60
AT+SMCONF="CLEANSS",1
AT+SMCONF="QOS",1
AT+SMCONF?

# Convert certs
AT+CSSLCFG="SSLVERSION",0,3
AT+CSSLCFG="CONVERT",2,"rootCA.crt"
AT+CSSLCFG="CONVERT",1,"deviceCert.pem","devicePrivateKey.pem"
AT+SMSSL=1,"rootCA.crt","deviceCert.pem"

# Connect to broker
AT+SMCONN

# Publish data
AT+SMPUB="$registries/are6phis3t903qjfrje3/events",93,0,1
{"ch1": "100", "ch1": "875759", "pressure": "20kPa", "charge": "76%", "safety_flags": "0x00"}
```

# Сборка на Linux
```
sudo apt-get install git make cmake libusb-1.0-0-dev
sudo apt-get install gcc build-essential

git clone https://github.com/stlink-org/stlink
cd stlink
cmake .
make

cd bin
sudo cp st-* /usr/local/bin
cd ../lib
sudo cp *.so* /lib32
cd ../

sudo cp config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
```