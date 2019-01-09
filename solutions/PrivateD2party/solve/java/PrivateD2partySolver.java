import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class PrivateD2partySolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> aBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] a = new int[aBoxed.size()];
        for (int _i = 0; _i < aBoxed.size(); ++_i)
            a[_i] = aBoxed.get(_i);
        reader.close();

        PrivateD2party solver = new PrivateD2party();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.getsz(a));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
