package travellingSalemansProblem;

import java.io.FileReader;
import java.util.Scanner;

import classesPb.Certificat;
import classesPb.NP;

public class testHamilton {

	/**
	 * @param args
	 */
	public static void main(String[] arg) throws Exception {
		// saisie du probleme
		if (arg.length < 3) {
			System.out.println("java testHamilton [-cycle|-path] mode file.ham");
		} else {
			// le probleme dans un fichier de donnees
			Scanner donnee = new Scanner(new FileReader(arg[2]));
			for (int i = 0; i < 3; i++) {
				donnee.nextLine();
			}
			donnee.next();
			int nbv = donnee.nextInt();
			for (int i = 0; i < 4; i++) {
				donnee.nextLine();
			}
			boolean D[][] = new boolean[nbv][nbv];
			for (int i = 0; i < nbv; i++) {
				for (int j = 0; j < nbv; j++) {
					D[i][j] = donnee.nextBoolean();
					System.out.print(D[i][j]+" ");
				}
				System.out.print("\n");
			}
			NP pb;
			if (arg[0].equals("-cycle")) {
				pb = new HamiltonCycleRed(nbv, D);
			} else if (arg[0].equals("-path")) {
				pb = new HamiltonPathRed(nbv, D);
			} else {
				System.out.println("erreur d'option, veuillez choisir entre les options -cycle ou -path");
				return;
			}
			System.out.println(arg[0]+" "+arg[1]);
			// les differents modes
			if (arg[1].equals("-verif")) {
				Certificat c = pb.cert();
				System.out.print("Proposez un certificat;");
				c.saisie();
				System.out.print("votre certificat est-il correct? ");
				System.out.println(pb.estCorrect(c));
			} else if (arg[1].equals("-nondet")) {
				System.out.println(pb.aUneSolutionNonDeterministe());
			} else if (arg[1].equals("-exhaust")) {
				System.out.println("le probleme a-t-il une solution?: ");System.out.println(pb.aUneSolution());
			} else if (arg[1].equals("-bogo")) {
				System.out.println("le probleme a-t-il une solution (bogo mode)?: ");System.out.println(pb.aUneSolutionBogo());
			} else {
				System.out.println("erreur de mode");
			}
		}
	}
}