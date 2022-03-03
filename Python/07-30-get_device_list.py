# #from __future__ import print_statement
# import time
# import iot_api_client as iot
# import openapi_client
# from openapi_client.rest import ApiException
# from pprint import pprint
#
#
# # Configure OAuth2 access token for authorization: oauth2
# openapi_client.configuration.access_token = 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJodHRwczovL2FwaTIuYXJkdWluby5jYy9pb3QiLCJhenAiOiJYcndNZ2F0RmVmcTVmWEhVZzBxTG9GNndJcjBKVDR5RiIsImV4cCI6MTY0NTU2ODk2MiwiZ3R5IjoiY2xpZW50LWNyZWRlbnRpYWxzIiwiaHR0cDovL2FyZHVpbm8uY2MvY2xpZW50X2lkIjoiQVBJLWRlbW9zIiwiaHR0cDovL2FyZHVpbm8uY2MvaWQiOiI5OWFmYzM4NS0zZTE3LTQ5M2ItYjBkMS0wNDJhZTQ0ZTUwZWEiLCJodHRwOi8vYXJkdWluby5jYy9yYXRlbGltaXQiOjEsImh0dHA6Ly9hcmR1aW5vLmNjL3VzZXJuYW1lIjoiZnV0dXJlc2hvY2tlZCIsImlhdCI6MTY0NTU2ODY2Miwic3ViIjoiWHJ3TWdhdEZlZnE1ZlhIVWcwcUxvRjZ3SXIwSlQ0eUZAY2xpZW50cyJ9.wCNR3wI9FQpoXQPqvi_D_NhCNudl6KzqpAxmL7BZIa0'

import iot_api_client as iot
from iot_api_client.rest import ApiException
from iot_api_client.configuration import Configuration

# configure and instance the API client
client_config = Configuration(host="https://api2.arduino.cc/iot")
client_config.access_token = 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJodHRwczovL2FwaTIuYXJkdWluby5jYy9pb3QiLCJhenAiOiJYcndNZ2F0RmVmcTVmWEhVZzBxTG9GNndJcjBKVDR5RiIsImV4cCI6MTY0NTY1MzM4OCwiZ3R5IjoiY2xpZW50LWNyZWRlbnRpYWxzIiwiaHR0cDovL2FyZHVpbm8uY2MvY2xpZW50X2lkIjoiQVBJLWRlbW9zIiwiaHR0cDovL2FyZHVpbm8uY2MvaWQiOiI5OWFmYzM4NS0zZTE3LTQ5M2ItYjBkMS0wNDJhZTQ0ZTUwZWEiLCJodHRwOi8vYXJkdWluby5jYy9yYXRlbGltaXQiOjEsImh0dHA6Ly9hcmR1aW5vLmNjL3VzZXJuYW1lIjoiZnV0dXJlc2hvY2tlZCIsImlhdCI6MTY0NTY1MzA4OCwic3ViIjoiWHJ3TWdhdEZlZnE1ZlhIVWcwcUxvRjZ3SXIwSlQ0eUZAY2xpZW50cyJ9.aMBl8fYxR_BzD2nP3QYK3PduhQ8BHBe9k4lgBJvHNdk'
client = iot.ApiClient(client_config)

# devices_api = iot.PropertiesV2Api(client)

# create an instance of the API class
api_instance = iot.DevicesV2Api()
# acrossUserIds = True # Boolean | If true, returns all the devices (optional) (default to false)
# serial = None # String | Filter by device serial number (optional) (default to null)
# tags = None # array[String] | Filter by tags (optional) (default to null)

try:
    # list devices_v2
    api_response = api_instance.devices_v2_list()
    pprint(api_response)
except ApiException as e:
    print("Exception when calling DevicesV2Api->devicesV2List: %s\n" % e)
