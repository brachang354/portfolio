from flask import redirect, request, url_for, render_template
from flask.views import MethodView
import gbmodel

class Sign(MethodView):
    def get(self):
        return render_template('sign.html')

    def post(self):
        """
        Accepts POST requests, and processes the form;
        Redirect to index when completed.
        """
        model = gbmodel.get_model()
        #model.insert(request.form['name'], request.form['email'], request.form['message'])
        model.insert(request.form['song_title'], request.form['genre'], request.form['artist'], request.form['date_released'])
        return redirect(url_for('index'))