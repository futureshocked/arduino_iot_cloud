from oauthlib.oauth2 import BackendApplicationClient
from requests_oauthlib import OAuth2Session

YOUR_CLIENT_ID = "XrwMgatFefq5fXHUg0qLoF6wIr0JT4yF"
YOUR_CLIENT_SECRET = "nFCmu8pBoXPnL1fH6Nw4AjszlyqKtH2uYJJM9cO0xs0MwiR6Iby1n0VMducmfY8E"

oauth_client = BackendApplicationClient(client_id=YOUR_CLIENT_ID)
token_url = "https://api2.arduino.cc/iot/v1/clients/token"

oauth = OAuth2Session(client=oauth_client)
token = oauth.fetch_token(
    token_url=token_url,
    client_id=YOUR_CLIENT_ID,
    client_secret=YOUR_CLIENT_SECRET,
    include_client_id=True,
    audience="https://api2.arduino.cc/iot",
)

print(token.get("access_token"))
