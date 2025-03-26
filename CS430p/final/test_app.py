#This is a test file to see if I can communicate with the Danbooru API

import requests
import os
import json
#import pprint

class api_booru():
    def get_booru(self, tag_string=None):
        #Getting api key from the shell
        api_key = os.environ.get('API_KEY')
        username = os.environ.get('USER_NAME')
        env_var = os.environ
        
        #API Credentials for the test website. Yes I know I shouldn't have my API key here but
        #it's only for the test website and I need a fast way to test my API calls
        test_api = ' '  #Removed test API_KEY just for security habits
        test_name = ' ' #Removed test USER_NAME just for security habits

        #To print environment variables to make sure they're set
        #pprint.pprint(dict(env_var), width = 1)

        #Base URL and test URL for Danbooru HTTP
        url = 'https://danbooru.donmai.us/'
        test_url = 'https://testbooru.donmai.us/'

        #error_json = {'success': False, 'error': 'ActiveRecord::RecordNotFound', 'message': 'That record was not found.', 'backtrace': ["app/controllers/posts_controller.rb:133:in `random'", "app/logical/rack_server_timing.rb:19:in `call'"]}

        #Query variables
        #tag_string = custom_tag

        #Test API response
        if tag_string == None:
            response = requests.get(f'{url}posts/random.json?api_key={api_key}&login={username}')
            
            #Test response
            #response = requests.get(f'{test_url}posts/random.json?api_key={test_api}&login={test_name}')
        else:
            response = requests.get(f'{url}posts/random.json?tags={tag_string}&api_key={api_key}&login={username}')

            #Test response
            #response = requests.get(f'{test_url}posts/random.json?tags={tag_string}&api_key={test_api}&login={test_name}')

        r = response.json()

        if('success' in r and not r['success']):
        #if(response.json()[0] == "False"):
            response = requests.get(f'{url}posts/random.json?api_key={api_key}&login={username}')

            #Test response
            #response = requests.get(f'{test_url}posts/random.json?api_key={test_api}&login={test_name}')
            r = response.json()
        
        #print(r)
        return r["file_url"]

def main():
    #Main for testing purposes
    api = api_booru()
    url = api.get_booru("frieren")
    print(url)

if __name__ == "__main__":
    main()