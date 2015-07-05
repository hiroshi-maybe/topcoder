import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class FallingSandSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<String> boardBoxed = (List<String>) reader.next(new TypeRef<List<String>>(){}.getType());
        String[] board = new String[boardBoxed.size()];
        for (int _i = 0; _i < boardBoxed.size(); ++_i)
            board[_i] = boardBoxed.get(_i);
        reader.close();

        FallingSand solver = new FallingSand();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        String[] result = solver.simulate(board);
        List<String> resultBoxed = new ArrayList<String>();
        for (int _i = 0; _i < result.length; ++_i) {
            resultBoxed.add(result[_i]);
        }
        writer.write(resultBoxed);
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
