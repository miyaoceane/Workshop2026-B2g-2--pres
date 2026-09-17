# Architecture du projet — RickLab

## Structure des dossiers

```
RickLab/
├── Documentation/
│   ├── architecture.md
│   ├── bibliotheques.md
│   ├── composants_utilises.md
│   ├── IA_utilises.md
│   ├── shemas.md
│   └── structure_logicielle.md
├── Page Web/
│   └── Page/
│       ├── background_img.jpg
│       ├── html.html
│       ├── script.js
│       └── style.css
│   └── Script/
│       ├── arduino.py
│       ├── ia.py
│       └── python.py
└── README.md

```

## Description des composants

| Dossier / Fichier      | Rôle                                                        |
|-------------------------|--------------------------------------------------------------|
| `Page Web/Page/`        | Frontend : interface utilisateur (HTML, CSS, JS)             |
| `Script/python.py`      | Serveur backend (Flask), fait le lien entre le front et l'IA  |
| `Script/ia.py`          | Logique d'analyse / intelligence artificielle                |
| `Script/arduino.py`     | Communication avec le matériel Arduino                       |
| `Documentation/`        | Schémas, bibliothèques et composants utilisés                |

## Flux général

1. L'utilisateur écrit une idée dans le formulaire (`html.html`)
2. Le formulaire envoie les données au serveur Flask (`python.py`)
3. `python.py` transmet les données à `ia.py` pour analyse
4. Le résultat est renvoyé et affiché côté frontend
5. `arduino.py` gère les interactions avec le matériel physique

## Améliorations à prévoir

- Ajouter un `requirements.txt` pour les dépendances Python
- Uniformiser les noms de dossiers (éviter les espaces)
