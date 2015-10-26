import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class LiveConcertSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> hBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] h = new int[hBoxed.size()];
        for (int _i = 0; _i < hBoxed.size(); ++_i)
            h[_i] = hBoxed.get(_i);
        reader.next();
        
        List<String> sBoxed = (List<String>) reader.next(new TypeRef<List<String>>(){}.getType());
        String[] s = new String[sBoxed.size()];
        for (int _i = 0; _i < sBoxed.size(); ++_i)
            s[_i] = sBoxed.get(_i);
        reader.close();

        LiveConcert solver = new LiveConcert();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.maxHappiness(h, s));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
