class Model():
    def select(self):
        """
        Gets all entries from the database
        :return: Tuple containing all rows of database
        """
        pass

    def insert(self, song_title, genre, artist, date_released):
        """
        Inserts song entry into database
        :param song_title: String
        :param genre: String
        :param artist: String
        :param date_released: String
        :return: none
        :raises: Database errors on connection and insertion
        """
        pass
