import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class BridgeBuildingDiv2Solver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> aBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] a = new int[aBoxed.size()];
        for (int _i = 0; _i < aBoxed.size(); ++_i)
            a[_i] = aBoxed.get(_i);
        reader.next();
        
        List<Integer> bBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] b = new int[bBoxed.size()];
        for (int _i = 0; _i < bBoxed.size(); ++_i)
            b[_i] = bBoxed.get(_i);
        reader.next();
        
        int K = (Integer) reader.next(Integer.class);
        reader.close();

        BridgeBuildingDiv2 solver = new BridgeBuildingDiv2();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.minDiameter(a, b, K));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
