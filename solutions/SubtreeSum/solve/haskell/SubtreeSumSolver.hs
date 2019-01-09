import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified SubtreeSum (getSum)

getVars :: TC.Parser ([Int], [Int])
getVars = do p <- TC.spaces >> (TC.parseList TC.parseInt) ; TC.spaces >> TC.next
             x <- TC.spaces >> (TC.parseList TC.parseInt)
             return (p, x)

main = do
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (p, x) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ SubtreeSum.getSum p x
            hClose hOut
    hClose hIn
