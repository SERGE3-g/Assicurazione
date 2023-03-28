import java.util.Scanner;

public class assicurazione{
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        // Input dati dell'assicurato
        System.out.print("Inserisci il tuo nome: ");
        String nome = input.nextLine();
        System.out.print("Inserisci il tuo cognome: ");
        String cognome = input.nextLine();
        System.out.print("Inserisci la tua età: ");
        int eta = input.nextInt();
        System.out.print("Hai avuto incidenti negli ultimi 5 anni? (Sì o No): ");
        input.nextLine(); // Consuma la nuova linea rimasta dopo input.nextInt()
        String incidenti = input.nextLine();

        // Calcolo della tariffa dell'assicurazione in base all'età e agli incidenti
        double tariffa = 0.0;
        if (eta < 25) {
            tariffa = 1500.0;
        } else if (eta >= 25 && eta < 40) {
            tariffa = 1000.0;
        } else if (eta >= 40 && eta < 60) {
            tariffa = 800.0;
        } else {
            tariffa = 500.0;
        }
        if (incidenti.equalsIgnoreCase("Sì")) {
            tariffa += 500.0;
        }


        // Output della tariffa dell'assicurazione
        System.out.println("Ciao " + nome + " " + cognome + ", la tua tariffa per l'assicurazione è di " + tariffa + " euro.");
    }
}
