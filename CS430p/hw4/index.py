from flask import render_template
from flask.views import MethodView
import gbmodel

class Index(MethodView):
    def get(self):
        """
        This will get all of the entries in the database in order to display them
        in our index.
        """
        model = gbmodel.get_model()
        #entries = [dict(name=row[0], email=row[1], signed_on=row[2], message=row[3] ) for row in model.select()]
        entries = [dict(song_title=row[0], genre=row[1], artist=row[2], date_released=row[3]) for row in model.select()]
        return render_template('index.html',entries=entries)