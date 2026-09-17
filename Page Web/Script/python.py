from flask import Flask, render_template, request
from ia import analyser
import serial #arduino
import time

app = Flask(__name__,
            template_folder="../Page",
            static_folder="../Page")

# arduino = serial.Serial("COM5", 9600)
# time.sleep(2)

@app.route("/")
def accueil():
    return render_template("html.html")

@app.route("/analyser",methods=["POST"])
def traiter():
    text = request.form["text"]
    resultat = analyser(text)
    
    # arduino.write((resultat + "\n").encode())
    return resultat

app.run(debug=False)
