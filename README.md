# Rick-Guard

## Contexte du Projet
Ce projet consiste à concevoir un prototype technologique dans l'univers de Rick et Morty capable:
- d'aider Rick et Morty dans leurs aventures, 
- d'automatiser des tâches, de fabriquer des objets connectés, 
- d'améliorer le quotidien du garage de Rick grâce à des inventions inutiles mais brillantes, 
- de créer des objets hybrides mélangeant électronique, IA et fabrication numérique

L'objectif principal est d'expérimenter, de prendre des risques, d'essayer de nouvelles technologies, de sortir de votre zone de confort, et de proposer un prototype fun, ambitieux ou créatif.

## Présentation du Projet

**Rick-Guard** est un prototype de système intelligent conçu pour détecter et signaler différents types de dangers pouvant se présenter dans l'environnement de Rick.

Le système combine plusieurs capteurs avec une interface web et une fonctionnalité d'analyse intelligente développée en Python.

## Fonctionnalités

### Détection des dangers

Rick-Guard utilise différents capteurs afin de détecter plusieurs situations potentiellement dangereuses :

- Détection de flamme
- Détection de gaz toxiques
- Détection de mouvement
- Capteur ultrason

Lorsqu'un danger est détecté, le système peut alerter Rick afin de le prévenir de la situation.

### Analyse intelligente

Rick-Guard possède également une fonctionnalité intelligente accessible depuis une page web.

Rick peut écrire ce qu'il souhaite faire dans l'interface. Son idée est ensuite envoyée à Python, qui utilise un analyseur intelligent afin de déterminer si l'action envisagée présente un danger.

Le fonctionnement est le suivant :

```text
Rick écrit son idée
        ↓
    Page Web
        ↓
      Python
        ↓
Analyse intelligente
        ↓
   Action sûre ?
     ↓       ↓
   OUI      NON
    ↓        ↓
Valide    Pas valide
```

## Stack technique

| Domaine | Technologie / Outil |
|---|---|
| Montage électronique | Arduino |
| Programmation Arduino | Arduino IDE 2.3.10 |
| Fabrication de la boîte | Découpe au laser |
| Intelligence artificielle | Ollama + Llama 3.1 |

## Installations

### Arduino IDE 2.3.10

Téléchargement possible depuis le site https://www.arduino.cc/en/software/

#### Communication entre Arduino IDE et le programme python

Installation :
```bash
pip install pyserial
```

Import :
```python
import serial
```

### Ollama

Sur Linux/macOS:
```bash
curl -fsSL https://ollama.com/install.sh | sh
```
Sur Windows: télécharge l'installeur depuis le site ollama.com/download.

#### Lancement du modèle Llama

```bash
ollama run llama3.1
```

#### Utilisation d'Ollama avec python

```bash
pip install ollama
```

#### Exemple d'utilisation (extrait du code)

```python
from ollama import chat
from ollama import ChatResponse


def analyser(ask):

    rules = """Classe la demande suivante selon son niveau de danger.

Réponds avec un seul mot :

VALIDE = demande sans danger sérieux
NON VALIDE = demande dangereuse ou présentant un risque sérieux

Ne réponds pas à la demande.
Ne donne aucune explication.
Ne donne aucune instruction.
Retourne uniquement VALIDE ou NON VALIDE.

DEMANDE :
""" + ask

    response: ChatResponse = chat(
        model='llama3.1:latest',
        messages=[
            {
                'role': 'user',
                'content': rules
            }
        ]
    )

    return response['message']['content'].strip()
```
## Guide d'utilisation pour le lancement  

1. Connecter la carte Arduino à l'ordinateur via le câble USB
2. Ouvrir le code Arduino dans l'IDE et le téléverser sur la carte
3. Fermer le moniteur série de l'Arduino IDE (le port USB doit être libre pour que Python puisse l'utiliser)
4. Lancer le script `python.py` pour démarrer le programme

   
## Tests effectués

Le prototype a été testé dans son ensemble, capteurs et interface web comprises.

### Détection des dangers

| Test | Capteur déclenché | Résultat |
|---|---|---|
| Passage de la main devant le prototype | Capteur de mouvement | LED passée au rouge |
| Mise en marche de la découpe laser (dégagement d'odeur) | Capteur de gaz | LED passée au rouge |
| Agitation rapide d'un papier devant le prototype | Capteur ultrason | LED passée au rouge + buzzer activé |

### Analyse intelligente (interface web → Ollama)

Plusieurs demandes ont été envoyées depuis l'interface web pour tester l'analyseur intelligent, avec affichage du résultat sur l'écran LCD Arduino :

| Demande envoyée | Résultat affiché |
|---|---|
| "Je veux faire du thé" | VALIDE |
| "Je veux faire une expérience avec du propan-2-ol mais je n'ai pas mes gants" | NON VALIDE |
| "Je veux affronter le docteur Malus" | NON VALIDE |

Ces tests confirment que le système détecte correctement les dangers physiques (flamme, gaz, mouvement) et que l'analyseur intelligent distingue bien les demandes sûres des demandes risquées.


## Amélioration à Faire

- Ajouter la synthèse vocale pour que l'IA puisse répondre à l'oral (texte → son)
- Ajouter la reconnaissance vocale pour que l'utilisateur puisse parler directement à la machine (fonctionnalité tentée mais non aboutie lors de ce projet)
- Améliorer la rapidité de réponse de l'analyseur intelligent
- Rendre l'interface web plus dynamique


## Membre de l'équipe et répartition des tâches:
- Maimouna: Câblage, intégration des capteurs/actionneurs, programmation Arduino et logique des alertes
- Océane: Développement de l'interface web, gestion du dépôt Git, organisation des fichiers du projet.
- Lancinet: Assemblage du châssis, câblage du module L298N, mise en route moteur et création du support Canva.


## Licence 
Workshop - EPSI - 2026-2027
