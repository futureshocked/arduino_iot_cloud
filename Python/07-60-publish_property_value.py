import json
import iot_api_client as iot
from iot_api_client.rest import ApiException
from iot_api_client.configuration import Configuration

# configure and instance the API client
client_config = Configuration(host="https://api2.arduino.cc/iot")
client_config.access_token = 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJodHRwczovL2FwaTIuYXJkdWluby5jYy9pb3QiLCJhenAiOiJYcndNZ2F0RmVmcTVmWEhVZzBxTG9GNndJcjBKVDR5RiIsImV4cCI6MTY0NTY1NTg3MywiZ3R5IjoiY2xpZW50LWNyZWRlbnRpYWxzIiwiaHR0cDovL2FyZHVpbm8uY2MvY2xpZW50X2lkIjoiQVBJLWRlbW9zIiwiaHR0cDovL2FyZHVpbm8uY2MvaWQiOiI5OWFmYzM4NS0zZTE3LTQ5M2ItYjBkMS0wNDJhZTQ0ZTUwZWEiLCJodHRwOi8vYXJkdWluby5jYy9yYXRlbGltaXQiOjEsImh0dHA6Ly9hcmR1aW5vLmNjL3VzZXJuYW1lIjoiZnV0dXJlc2hvY2tlZCIsImlhdCI6MTY0NTY1NTU3Mywic3ViIjoiWHJ3TWdhdEZlZnE1ZlhIVWcwcUxvRjZ3SXIwSlQ0eUZAY2xpZW50cyJ9.OrttSylUoe1mQRmGxsd98eiHfwHkpmXU7BeDclfRLhA'
client = iot.ApiClient(client_config)

# as an example, interact with the devices API
devices_api = iot.PropertiesV2Api(client)
id = "4ad96e22-6882-46c6-858f-764ae38b62e6" # String | The id of the thing (default to null)
pid = "faf92fcf-8c61-4e85-b5d6-5c1683ced9ff" # String | The id of the property (default to null)
propertyValue =  {"device_id" : "4f233499-5497-49b4-9569-8df938817c13", "value" : "Msg 20"}

try:
    resp = devices_api.properties_v2_publish(id, pid, propertyValue)
except ApiException as e:
    print("Exception when calling PropertiesV2Api->propertiesV2Publish: %s\n" % e)
