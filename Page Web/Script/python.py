from flask import Flask, render_template, request
from ia import analyser
import serial #arduino
import time

# Création de l'instance de l'application Web Flask
app = Flask(__name__,
            template_folder="../Page",
            static_folder="../Page")

# Connection avec le port COM5
arduino = serial.Serial("COM5", 9600)
time.sleep(2)

"""    AFFICHAGE DE LA PAGE HTML   """

@app.route("/") # Création de la premiere route 
def accueil():
    return render_template("html.html")

"""   TRAITEMENT DU TEXTE RÉCUPÉRÉ DANS LA ZONE DE TEXTE   """

@app.route("/analyser", methods=["POST"]) # Création de la route pour l'analyse et on accepte que les requêtes du type POST
def traiter():
    text = request.form["text"] # récupération du texte
    resultat = analyser(text)

    print("Résultat de l'analyse :", resultat) # affiche le résultat dans la console Python

    arduino.write((resultat + "\n").encode()) # Envoie la réponse à Arduino
    return resultat # renvoie le vrai résultat à la page web

app.run(debug=False) # Faire tourner l'app Flask