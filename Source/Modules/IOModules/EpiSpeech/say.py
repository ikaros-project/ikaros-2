#!/usr/bin/env python3.11
#
# Assuming EpiSpeech_test.ikg is running
#

import requests
import urllib.parse

def say(text):
    base_url = "http://localhost:8000"
    command = "command/EpiSpeech.say/0/0/"
    encoded_string = urllib.parse.quote(text)
    full_url = f"{base_url}/{encoded_string}"

    response = requests.get(full_url)

    if response.status_code == 200:
        print("Response received successfully!")
        print(response.JSON)
    else:
        print(f"Request failed with status code: {response.status_code}")



say("Hello, I am Epi the robot!")


