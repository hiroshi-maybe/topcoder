import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class DivisibleSetDiv2Solver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> bBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] b = new int[bBoxed.size()];
        for (int _i = 0; _i < bBoxed.size(); ++_i)
            b[_i] = bBoxed.get(_i);
        reader.close();

        DivisibleSetDiv2 solver = new DivisibleSetDiv2();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.isPossible(b));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
