import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class XylophoneSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> keysBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] keys = new int[keysBoxed.size()];
        for (int _i = 0; _i < keysBoxed.size(); ++_i)
            keys[_i] = keysBoxed.get(_i);
        reader.close();

        Xylophone solver = new Xylophone();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.countKeys(keys));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
