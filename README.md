# Operating Systems Workspace

Dieses Repository enthält eine strukturierte Entwicklungsumgebung für die Programmieraufgaben im Modul **Betriebssysteme**.  
Ziel ist es, die Aufgaben **übersichtlich**, **reproduzierbar** und **ohne unnötigen technischen Aufwand** bearbeiten zu können.

Die Struktur ist so aufgebaut, dass:

- jede Aufgabe für sich steht
- die vom KIT bereitgestellten Makefiles und Tests unverändert bleiben
- Bauen und Testen möglichst einfach sind

## Voraussetzungen

Empfohlene Umgebung:

- Ubuntu 20.04 oder neuer
- Visual Studio Code

Installation der benötigten Pakete unter Ubuntu:

```bash
sudo apt update
sudo apt install build-essential gawk python3
```

## Assignments importieren

Die vom KIT bereitgestellten Template-Archive (`asstXX-templates.tar.gz`) werden **nicht manuell entpackt**, sondern über ein Skript importiert.

### Vorgehen

1. Die Template-Archive in den Ordner `import/` kopieren
2. Das Import-Skript ausführen:

    ```bash
    python3 tools/import_templates.py
    ```

Das Skript entpackt die Archive und legt die Assignments im Ordner `assignments/` ab.

## Repository-Struktur

```bash
operating_systems/
├── .vscode/
│   ├── launch.json          # Debuggen
│   └── tasks.json           # Build-Tasks
│
├── assignments/             # Alle importierten Assignments
│   ├── A01/
│   ├── A02/
│   └── ...
│
├── import/                  # Hier liegen die heruntergeladenen Template-Archive
│
├── tools/
│   ├── import_templates.py  # Importiert Assignment-Templates
│   └── test_assignment.py   # Baut & testet alle Tasks eines Assignments
│
└── README.md
```

## Ein Assignment testen

Im Assignment-Ordner (z.B. `assignments/A01`) kann mit folgendem Befehl das Assignment gebaut und getestet werden:

```bash
python3 ../tools/test_assignment.py
```

Der Befehlt kann **nur aus dem Assignment-Ordner** heraus ausgeführt werden.

## Wichtige Hinweise

- Makefiles, `testlib` und `testrunner` nicht verändern
- Pro Aufgabe nur die zugehörigen `.c`` Dateien bearbeiten
- Änderungen an den Templates oder der Struktur können dazu führen, dass Tests nicht mehr korrekt laufen
