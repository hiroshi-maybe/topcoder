import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class ArrfixSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> ABoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] A = new int[ABoxed.size()];
        for (int _i = 0; _i < ABoxed.size(); ++_i)
            A[_i] = ABoxed.get(_i);
        reader.next();
        
        List<Integer> BBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] B = new int[BBoxed.size()];
        for (int _i = 0; _i < BBoxed.size(); ++_i)
            B[_i] = BBoxed.get(_i);
        reader.next();
        
        List<Integer> FBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] F = new int[FBoxed.size()];
        for (int _i = 0; _i < FBoxed.size(); ++_i)
            F[_i] = FBoxed.get(_i);
        reader.close();

        Arrfix solver = new Arrfix();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.mindiff(A, B, F));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
