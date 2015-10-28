import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified IsItASquare (isSquare)

getVars :: TC.Parser ([Int], [Int])
getVars = do x <- TC.spaces >> (TC.parseList TC.parseInt) ; TC.spaces >> TC.next
             y <- TC.spaces >> (TC.parseList TC.parseInt)
             return (x, y) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (x, y) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ IsItASquare.isSquare x y
            hClose hOut
    hClose hIn