""" ON IMPORTE OLLAMA """

from ollama import chat
from ollama import ChatResponse


def analyser(ask):

#On envoie une conisgne précise à l'IA pour éviter des réponses non attendu
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