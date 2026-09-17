## Architecture du projet 
<img width="750" height="474" alt="Capture d&#39;écran 2026-09-17 135105" src="https://github.com/user-attachments/assets/ae5ebddc-7e4e-4691-a0f5-58125fb5bf8b" />

## Flux général

1. L'utilisateur écrit une idée dans le formulaire (`html.html`)
2. Le formulaire envoie les données au serveur Flask (`python.py`)
3. `python.py` transmet les données à `ia.py` pour analyse
4. Le résultat est renvoyé et affiché côté frontend
5. `arduino.py` gère les interactions avec le matériel physique
