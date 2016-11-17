import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class PartisanGameSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int n = (Integer) reader.next(Integer.class);
        reader.next();
        
        List<Integer> aBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] a = new int[aBoxed.size()];
        for (int _i = 0; _i < aBoxed.size(); ++_i)
            a[_i] = aBoxed.get(_i);
        reader.next();
        
        List<Integer> bBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] b = new int[bBoxed.size()];
        for (int _i = 0; _i < bBoxed.size(); ++_i)
            b[_i] = bBoxed.get(_i);
        reader.close();

        PartisanGame solver = new PartisanGame();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.getWinner(n, a, b));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
