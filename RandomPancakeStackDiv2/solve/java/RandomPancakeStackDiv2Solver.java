import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class RandomPancakeStackDiv2Solver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> dBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] d = new int[dBoxed.size()];
        for (int _i = 0; _i < dBoxed.size(); ++_i)
            d[_i] = dBoxed.get(_i);
        reader.close();

        RandomPancakeStackDiv2 solver = new RandomPancakeStackDiv2();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.expectedDeliciousness(d));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
