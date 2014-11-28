

$HOST_A = "-pw end2endtest stefan@192.168.0.100"
$HOST_B = "-pw 123456 persistet@192.168.0.101"

$WORK_DIR = "~/work/HPPP_Controller/ScriptsHelper"
$DECENTRALICED_RUN_CMD = "bash -l ./runXDecentralized.sh"

$SAMPLE_TIME = 120
$WAIT_TURBINES_TIME = $SAMPLE_TIME + 10  #NEEDS CALIBRATION

$OUTFILE = "remoteCmd.txt"

Function StartRemoteTurbine{
  Param ([string]$HOST_SYSTEM = 0, [int]$nTurbines = 0, [int]$mSleep = 20)
  $remoteCmd = "cd $WORK_DIR && bash -l ./runXDecentralized.sh $nTurbines"

  $Utf8NoBomEncoding = New-Object System.Text.UTF8Encoding($False)
  [System.IO.File]::WriteAllLines($OUTFILE, $remoteCmd, $Utf8NoBomEncoding) 

  $CMD = [scriptblock]::Create("..\Tools\putty.exe -ssh -t $HOST_SYSTEM -m $OUTFILE")
  Invoke-Command -scriptblock $CMD

  Write-Host $CMD
}

Function KilleRemoteTurbines{
  Param ()
  $remoteCmd = """killall -9 DecentralizedParkPilot"""
  $CMD = [scriptblock]::Create("..\Tools\putty.exe -ssh -t $HOST_SYSTEM $remoteCmd")
#  Invoke-Command -scriptblock $CMD

  Write-Host $CMD
}

Function OpenMatlab{
  Param ()
  $CMD = [scriptblock]::Create("..\ScriptsHelper\runDecentralizedWindParkLog.bat $SAMPLE_TIME")
  Invoke-Command -scriptblock $CMD

  Write-Host $CMD

  sleep 5
}

for ([int]$nTurbines=5; $nTurbines -le 101; $nTurbines += 5){  
  $nTurbinesA = [math]::floor($nTurbines / 2)
  $nTurbinesB = [math]::Ceiling($nTurbines / 2)
  
  StartRemoteTurbine $HOST_A $nTurbinesAn
#  StartRemoteTurbine $HOST_B $nTurbinesB
#  OpenMatlab

  sleep $WAIT_TURBINES_TIME
}


#$CMD = $("../putty.exe -ssh -pw end2endtest -t " + $HOST_A + """ cd " + $WORK_DIR + " && " + $DECENTRALICED_RUN_CMD + " " + $nTurbines + """")  


#$command = { get-eventlog -log "windows powershell" | where {$_.message -like "*certificate*"} }
#invoke-command -computername Server64, Server65, Server102 -scriptblock $command

