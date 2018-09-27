C++ Semesterarbeit II (Sose) - Jürgen Schmitz - Stand 24.9.2018


Beschreibung des Business Case: Ein basales 2D-Shoot-em-Up Game soll entwickelt werden.


Vorgehensweise: 
Sprint1: Spielfeld & Avatar
* Bau einer  2-dimensionalen Zeichenfläche 
   * Erschaffen eines Zeichenfeld-Objekts “avatar” 
         * Erschaffen eines 2D-Referenzpunktes “point” und Verstauen des Punkts in einen objektspezifischen Vektor “points”
            * Erschaffen einer int-Variable zur Definierung der X-Koordinate des Avatars “x_koordinate”
               * Herauffzählen / Herabzählen von “x_koordinate” durch MouseEvent
                  * Abdrucken des Zeichenfeld-Objekts anhand des Referenzpunkts im Vektor mithilfe des Iterators “pos” bei jedem paintEvent

Sprint 2: (De-)Serialisierung-Setup
* Bau einer Serialisierungsfunktion /Deserialisierungsfunktion für die Position des Avatars “x_koordinate”
   * Verknüpfen der Funktion mit einem Dateiformat
      * Verknüpfen der Funktionen mit einem jeweiligen Knopf “Load” und ”Save”

Sprint 3: Fallende Objekte
* Erschaffen eines Zeichenfeld-Objekts “hagelkoerner” 
      * Erschaffen mehrerer 2D-Referenzpunkte “point” und Verstauen der Punkte in einen objektspezifischen  Vektor “points”
         * Iterieren aller Punkte im Vektor “points”
            * Verringerung der y-Koordinate jedes einzelnen Punktes  via ”setY()” im Rhythmus der Timer-Function
               * Abdrucken der Zeichenfeld-Objekte anhand der Referenzpunkte im Vektor “points” mithilfe des Iterator “posHagel” bei jedem paintEvent

Sprint 4: Highscore
* Erschaffen einer int-Variable “counter”
   * Heraufzählen bei jedem paintEvent 
      * int “counter” in Qstring “numberofPoints” überspielen
         * QString mit drawText() bei jedem PaintEvent abdrucken

Sprint 5: Leben des Avatars
* Erstellung einer objektspezifischen int-Variable “lives” zur Definierung der Leben des Avatars mit einem default-Wert von 3
   * Erschaffen eines Zeichenfeld-Objekts “hearts” 
         * Erschaffen mehrerer 2D-Referenzpunkte “point” in der Höhe von “lives” 
         * Verstauen der Punkte in einen objektspezifischen  Vektor “points”
            * Iterieren aller Punkte im Vektor “points”
               * Abdrucken der Zeichenfeld-Objekte anhand der Referenzpunkte  im Vektor “points” mithilfe des Iterator “pos” bei jedem paintEvent

Sprint 6: (De-)Serialisierung finalisieren
* Erweiterung der (De-)Serialisierungsfunktion auf alle Zeichenfeld-Objekte und die Avatar-Variablen
   * Speicherung aller Koordinaten und Variablen innerhalb der serialisierten Datei
   * Deserialiserung der Daten in die Datenstruktur

Sprint 7: Kollision abfangen
* Berechnen aller von den Zeichenfeld-Objekte “hagelkoerner” und “avatar” eingenommenen 2D-Punkte ausgehend vom Referenzpunkt bei jedem PaintEvent
   * Abgleich jedes enthaltenen Punkts von “avatar” mit jedem enthaltenen Punkt von“hagelkoerner” 
      * bei Überschneidung Verringerung der int-Variable “lives”
         * Ausbrechen aus dem for-loop

Repository Permalink: https://github.com/DerSchmitz/semesterarbeit2_ss2018
