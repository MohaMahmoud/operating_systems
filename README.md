# Operating Systems Workspace

Dieses Repository enthält eine strukturierte Entwicklungsumgebung für die Programmieraufgaben im Modul **Betriebssysteme**.  
Ziel ist es, die Aufgaben **übersichtlich** und **ohne unnötigen technischen Aufwand** bearbeiten zu können.

## Voraussetzungen

Empfohlene Umgebung:

- Ubuntu 20.04 oder neuer
- Visual Studio Code

Installation der benötigten Pakete unter Ubuntu:

```bash
sudo apt update
sudo apt install build-essential gawk python3
```

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

## Assignments importieren

Die vom KIT bereitgestellten Template-Archive (`asstXX-templates.tar.gz`) werden **nicht manuell entpackt**, sondern über ein Skript importiert.

### Vorgehen

1. Die Template-Archive in den Ordner `import/` kopieren
2. Das Import-Skript ausführen:

    ```bash
    python3 tools/import_templates.py
    ```

## Ein Assignment testen

Im Assignment-Ordner (z.B. `assignments/A01`) kann mit folgendem Befehl das Assignment gebaut und getestet werden:

```bash
python3 ../tools/test_assignment.py
```

**Tipp**: Ein alias kann hier sehr hilfreich sein.

## Wichtige Hinweise

- Makefiles, `testlib` und `testrunner` nicht verändern
- Pro Aufgabe nur die zugehörigen `.c`` Dateien bearbeiten
- Änderungen an den Templates oder der Struktur können dazu führen, dass Tests nicht mehr korrekt laufen
