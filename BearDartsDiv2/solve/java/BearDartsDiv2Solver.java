import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class BearDartsDiv2Solver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> wBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] w = new int[wBoxed.size()];
        for (int _i = 0; _i < wBoxed.size(); ++_i)
            w[_i] = wBoxed.get(_i);
        reader.close();

        BearDartsDiv2 solver = new BearDartsDiv2();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.count(w));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
