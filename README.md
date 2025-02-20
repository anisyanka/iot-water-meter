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
