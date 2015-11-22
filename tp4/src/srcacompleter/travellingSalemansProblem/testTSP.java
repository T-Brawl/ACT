package travellingSalemansProblem;
import java.io.*;
import java.util.Scanner;


public class testTSP{  

public static void main(String[] arg) throws Exception {
 	//saisie du probleme
	if (arg.length < 3)
	    System.out.println("java testTSP mode file.atsp lg");
	else {
		int lg=Integer.parseInt(arg[2]);	
		//le probleme dans un fichier de donnees
		Scanner donnee = new Scanner (new FileReader(arg[1]));
		
		for (int i=0; i<3; i++) donnee.nextLine();
		
		donnee.next();
   
		int nbv = donnee.nextInt();	 
    
		for (int i=0; i<4; i++) donnee.nextLine();
    
		int D[][]=new int[nbv][nbv];
		for (int i=0; i<nbv; i++){
			for (int j=0; j<nbv; j++) {
				D[i][j]= donnee.nextInt();
				System.out.print(D[i][j]+" ");
				}
			System.out.println();
		}
		
		donnee.close();
		TSP pb = new TSP(nbv,D,lg);
		
		System.out.println(arg[0]);
		
		// les differents modes
		if (arg[0].equals("-verif")) { 
			CertificatTSP c = pb.cert();
			System.out.print("Proposez un certificat;");
			c.saisie();
			System.out.print("votre certificat est-il correct? :\n"+pb.estCorrect(c));
    	}
		else if (arg[0].equals("-nondet")) {
			System.out.println(pb.aUneSolutionNonDeterministe());
        }
		else if (arg[0].equals("-exhaust"))  { 
			System.out.println("le probleme a-t-il une solution? :\n"+pb.aUneSolution());
		} 
		else if (arg[0].equals("-bogo")) {
			System.out.println("le probleme a-t-il une solution (bogo mode)? :\n"+pb.aUneSolutionBogo());
    	}
		else System.out.println("erreur de mode");
	}
}

}
