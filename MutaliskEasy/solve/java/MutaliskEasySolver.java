import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class MutaliskEasySolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> xBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] x = new int[xBoxed.size()];
        for (int _i = 0; _i < xBoxed.size(); ++_i)
            x[_i] = xBoxed.get(_i);
        reader.close();

        MutaliskEasy solver = new MutaliskEasy();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.minimalAttacks(x));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
