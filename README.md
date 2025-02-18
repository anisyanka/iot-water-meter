Консоль облака: https://console.yandex.cloud/folders/b1g11ldc88cj7vpl7tba

# Шаги по развёртыванию IoT-инфраструктуры

## Первичные действия
1. Создать платёжный аккаунт - https://yandex.cloud/ru/docs/iot-core/quickstart#before-you-begin
2. Получить личный токен: https://oauth.yandex.ru/authorize?response_type=token&client_id=1a6990aa636648e9b2ef855fa7bec2fb
3. Настроить CLI - https://yandex.cloud/ru/docs/cli/quickstart#install
4. Сгенерировать сертификат реестра усройств
```bash
openssl req -x509 \
-newkey rsa:4096 \
  -keyout private-key-water-meter-telemetry.pem
  -out cert-water-meter-telemetry.pem
  -nodes \
  -days 365 \
  -subj '/CN=localhost'
```
5. Создать  реестр, где будут все устройства
```bash
yc iot registry create --name "water-meter-telemetry" --description "Test register for water meter MQTT sensors"
```
6. Добавить ранее созданный сертификат для нового реестра
```bash
yc iot registry certificate add \
   --registry-name "water-meter-telemetry" \
   --certificate-file register/cert-water-meter-telemetry.pem
```

## Добавление нового устройства в реестр (повторить для каждого нового устройства)
7. Сгенерировать сертификат устройства
```bash
openssl req -x509 \
-newkey rsa:4096 \
  -keyout private-key-dev-sim7080-module.pem
  -out cert-dev-sim7080-module.pem
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
  --certificate-file devices/cert-dev-sim7080-module.pem
```
