import java.util.*;

class Player {
	String name;
	int score;

	Player(String name, int score) {
		this.name = name;
		this.score = score;
	}
}

class Checker implements Comparator<Player> {
  	// complete this method
	public int compare(Player a, Player b) {
        if (a.score != b.score) {
            return b.score - a.score;
        }
        return compareName(a.name, b.name);
    }
    
    private int compareName(String a, String b) {

        int lastIndex = a.length() > b.length() ? b.length() : a.length();
        for (int i = 0; i < lastIndex; i++) {
            if (a.charAt(i) == b.charAt(i)) continue;
            return a.charAt(i) - b.charAt(i);
        }
        return a.length() > b.length() ? 1 : -1;
    }
}

