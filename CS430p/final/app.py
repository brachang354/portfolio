"""
Bradley Chang 
A simple random anime image generator
Pulls a random image from the Danbooru art database
Users can optionally include tags to pull a random image with matching tags.
"""
import os
from flask import Flask, request, jsonify, render_template
from test_app import api_booru

app = Flask(__name__)
booru_api = api_booru()

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/get_image', methods=['GET'])
def get_image():
    tag = request.args.get('tag', '')  # Get the tag from the request
    image_url = booru_api.get_booru(tag if tag else None)  # Call your API
    return jsonify({'image_url': image_url})  # Return the URL as JSON

if __name__ == '__main__':
    #app.run(host='0.0.0.0', port=5000, debug=True)
    app.run(host='0.0.0.0',port=int(os.environ.get('PORT',5000)))