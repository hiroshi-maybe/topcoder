import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class SubtreeSumSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> pBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] p = new int[pBoxed.size()];
        for (int _i = 0; _i < pBoxed.size(); ++_i)
            p[_i] = pBoxed.get(_i);
        reader.next();
        
        List<Integer> xBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] x = new int[xBoxed.size()];
        for (int _i = 0; _i < xBoxed.size(); ++_i)
            x[_i] = xBoxed.get(_i);
        reader.close();

        SubtreeSum solver = new SubtreeSum();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.getSum(p, x));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
