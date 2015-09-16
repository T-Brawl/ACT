package comparaisons;

public class FonctionsReference {

	private int[] sizes;

	public FonctionsReference(int[] sizes) {
		this.sizes = sizes;
	}
	
	/**
	 * Retourne le tableau de toutes les valeurs de n^pow pour tous
	 * les n présents dans this.sizes.
	 * @param pow puissance
	 * @return tableau des résultats
	 */
	public double[] puissance (double pow) {
		double[] values = new double[this.sizes.length];
		
		for (int idx=0 ; idx<this.sizes.length ; idx++)
			values[idx] = Math.pow(this.sizes[idx], pow);
		
		return values;
	}
	
	/**
	 * Retourne le tableau de toutes les valeurs de n^pow pour tous
	 * les n présents dans this.sizes.
	 * @param pow puissance
	 * @return tableau des résultats
	 */
	public double[] logarithme () {
		double[] values = new double[this.sizes.length];
		
		for (int idx=0 ; idx<this.sizes.length ; idx++)
			values[idx] = Math.log(this.sizes[idx]);
		
		return values;
	}
	
	/**
	 * 
	 * @return
	 */
	public double[] nlogn() {
		double[] values = new double[this.sizes.length];
		
		for (int idx=0 ; idx<this.sizes.length ; idx++)
			values[idx] = this.sizes[idx] * Math.log(this.sizes[idx]);
		
		return values;
	}
	
	/**
	 * 
	 * @return
	 */
	public double[] exp() {
		double[] values = new double[this.sizes.length];
		
		for (int idx=0 ; idx<this.sizes.length ; idx++)
			values[idx] = Math.exp(this.sizes[idx]);
		
		return values;
	}
	
	
	public double[] puissancen (int k) {
		double[] values = new double[this.sizes.length];
		
		for (int idx=0 ; idx<this.sizes.length ; idx++)
			values[idx] = Math.pow(k, this.sizes[idx]);
		
		return values;
	}
	
	public double[] factorielle () {
		double[] values = new double[this.sizes.length];
		double res = 1;
		int cpt=1;
		for (int idx=0 ; idx<this.sizes.length ; idx++) {
			int i;
			for (i=cpt; i<=this.sizes[idx];i++) res *= i;
			values[idx] = res;
			cpt=i;
		}	
		return values;
	}
	
	public double[] npuissancen () {
		double[] values = new double[this.sizes.length];
		
		for (int idx=0 ; idx<this.sizes.length ; idx++)
			values[idx] = Math.pow(this.sizes[idx], this.sizes[idx]);
		
		return values;
	}
	
}
