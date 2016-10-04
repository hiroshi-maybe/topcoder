import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified UpDownHiking (maxHeight)

getVars :: TC.Parser (Int, Int, Int)
getVars = do n <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             a <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             b <- TC.spaces >> TC.parseInt
             return (n, a, b)

main = do
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (n, a, b) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ UpDownHiking.maxHeight n a b
            hClose hOut
    hClose hIn
