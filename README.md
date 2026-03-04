# Program za razmenu poruka (C, shared memory + semafori)

Ovo je jednostavan primer međuprocesne komunikacije (IPC) u programskom jeziku C.  
Dva procesa (`sender` i `receiver`) razmenjuju **tekstualnu poruku** preko:

- deljene memorije (POSIX shared memory),
- imenovanih semafora (POSIX semaphores) za sinhronizaciju pristupa.

Aplikacija još uvek nije potpuno završena (npr. nema višestruke poruke, chat u oba smera i sl.), već je zamišljena kao **postepeni projekat**.

## Kako se pokreće

### 1. Kompajliranje

U root folderu projekta (gde je `Makefile`) pokrenuti:

```bash
make
```

Ovo će napraviti sledeće izvršne fajlove u folderu `bin`:

- `sender`
- `receiver`
- `cleanup`

### 2. Slanje i prijem jedne poruke

Najbolje je koristiti **dva terminal prozora**.

1. U prvom terminalu pokrenuti `receiver` (on čeka poruku):

   ```bash
   cd /Aros
   ./bin/receiver
   ```

2. U drugom terminalu pokrenuti `sender` i uneti poruku:

   ```bash
   cd /Aros
   ./bin/sender
   ```

   Program će pitati da se unese tekst poruke, npr:

   ```text
   Sender: unesi poruku (max 255 znakova):
   ```

   Kada se pritisne Enter, poruka se upisuje u deljenu memoriju, a `receiver` je očitava i ispisuje.

### 3. Čišćenje resursa (shared memory + semafori)

Ako želiš da obrišeš IPC resurse (deljenu memoriju i semafore) koje program koristi, možeš da pokreneš:

```bash
cd /Aros
./bin/cleanup
```

Ovaj program će pokušati da:

- ukloni shared memory segment,
- ukloni oba semafora koja se koriste u aplikaciji.

