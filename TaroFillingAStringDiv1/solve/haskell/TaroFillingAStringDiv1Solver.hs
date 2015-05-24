import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified TaroFillingAStringDiv1 (getNumber)

getVars :: TC.Parser (Int, [Int], String)
getVars = do n <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             position <- TC.spaces >> (TC.parseList TC.parseInt) ; TC.spaces >> TC.next
             value <- TC.spaces >> TC.parseString
             return (n, position, value) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (n, position, value) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ TaroFillingAStringDiv1.getNumber n position value
            hClose hOut
    hClose hIn