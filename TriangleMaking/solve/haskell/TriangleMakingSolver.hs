import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified TriangleMaking (maxPerimeter)

getVars :: TC.Parser (Int, Int, Int)
getVars = do a <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             b <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             c <- TC.spaces >> TC.parseInt
             return (a, b, c)

main = do
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (a, b, c) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ TriangleMaking.maxPerimeter a b c
            hClose hOut
    hClose hIn
