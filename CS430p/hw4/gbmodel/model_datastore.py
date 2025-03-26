from .Model import Model
from datetime import datetime
from google.cloud import datastore

def from_datastore(entity):
    if not entity:
        return None
    if isinstance(entity, list):
        entity = entity.pop()
    #return [entity['name'],entity['email'],entity['date'],entity['message']]
    return [entity['song_title'], entity['genre'], entity['artist'], entity['date_released']]

class model(Model):
    def __init__(self):
        self.client = datastore.Client('cloud-chang-brachang')

    def select(self):
        query = self.client.query(kind = 'Songs')
        #query = self.client.query(kind = 'Review')
        entities = list(map(from_datastore,query.fetch()))
        return entities

    #def insert(self,name,email,message):
    def insert(self,song_title, genre, artist, date_released):
        key = self.client.key('Songs')
        #key = self.client.key('Review')
        rev = datastore.Entity(key)
        rev.update( {
            'song_title' : song_title,
            'genre' : genre,
            'artist' : artist,
            'date_released' : date_released
            })
        self.client.put(rev)
        return True