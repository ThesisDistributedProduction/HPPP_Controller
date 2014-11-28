

$HOST_A = "-pw end2endtest stefan@192.168.0.100"
$HOST_B = "-pw 123456 persistet@192.168.0.101"

$WORK_DIR = "~/work/HPPP_Controller/ScriptsHelper"
$DECENTRALICED_RUN_CMD = "bash -l ./runXDecentralized.sh"

$SAMPLE_TIME = 60
$WAIT_TURBINES_TIME = $SAMPLE_TIME + 25  #NEEDS CALIBRATION

$OUTFILE = ".\remoteCmd.txt"

Function runCmd{
  Param ([string]$HOST_SYSTEM = 0, [string]$remoteCmd = 0)

  if(Test-Path $OUTFILE){
    Remove-Item $OUTFILE
    sleep 0.5
  }

  new-item $OUTFILE -type file -value $remoteCmd

  $CMD = [scriptblock]::Create("..\Tools\putty.exe -ssh -t $HOST_SYSTEM -m $OUTFILE")
  Invoke-Command -scriptblock $CMD

  Write-Host $CMD
}

Function StartRemoteTurbine{
  Param ([string]$HOST_SYSTEM = 0, [int]$nTurbines = 0, [int]$mSleep = 20, [int]$startId = 0, [bool]$isCentralized)

  $remoteCmd = ""

  if ($isCentralized) {
     $remoteCmd = "cd $WORK_DIR && bash -l ./runXCentralized.sh $nTurbines $startId $mSleep" 
  }
  else {
    $remoteCmd = "cd $WORK_DIR && bash -l ./runXDecentralized.sh $nTurbines $startId $mSleep"    
  }

  runCmd $HOST_SYSTEM $remoteCmd
}

Function KilleRemoteTurbines{
  Param ()

  Stop-Process -processname putty*  
}

Function OpenMatlab{
  Param ([bool]$isCentralized)

  if ($isCentralized) {
    $CMD = [scriptblock]::Create("..\ScriptsHelper\runCentralizedWindParkLog.bat $SAMPLE_TIME")
    Invoke-Command -scriptblock $CMD

    Write-Host $CMD
  }
  else {
    $CMD = [scriptblock]::Create("..\ScriptsHelper\runDecentralizedWindParkLog.bat $SAMPLE_TIME")
    Invoke-Command -scriptblock $CMD

    Write-Host $CMD
  }

  sleep 5
}

Function TestVariableNumeberOfTurbines {
  param([string]$HOST_A = 0, [string]$HOST_B = 0, [int]$WAIT_TURBINES_TIME = 0, [bool]$isCentralized)
  
  $cycleSleep = 20

  for ([int]$nTurbines=5; $nTurbines -le 101; $nTurbines += 5){  
    $nTurbinesA = [math]::floor($nTurbines / 2)
    $nTurbinesB = [math]::Ceiling($nTurbines / 2)
    
    StartRemoteTurbine $HOST_A $nTurbinesA $cycleSleep 1 $isCentralized
    StartRemoteTurbine $HOST_B $nTurbinesB $cycleSleep 50 $isCentralized

    OpenMatlab $isCentralized

    sleep $WAIT_TURBINES_TIME
    KilleRemoteTurbines
  }
}

Function TestVariableSleepTime {
  param([string]$HOST_A = 0, [string]$HOST_B = 0, [int]$WAIT_TURBINES_TIME = 0, [bool]$isCentralized)

  for ([int]$nCycleSleep=5; $nCycleSleep -le 51; $nCycleSleep += 5) {
    StartRemoteTurbine $HOST_A 50 $nCycleSleep 1 $isCentralized
    StartRemoteTurbine $HOST_B 50 $nCycleSleep 50 $isCentralized
    
    OpenMatlab $isCentralized

    sleep $WAIT_TURBINES_TIME
    KilleRemoteTurbines 
  }
}

Function runTests{
  param([string]$HOST_A = 0, [string]$HOST_B = 0, [int]$WAIT_TURBINES_TIME = 0)
  
  # Decentralized tests #
  $isCentralized = $false

  #TestVariableNumeberOfTurbines $HOST_A $HOST_B $WAIT_TURBINES_TIME $isCentralized
  #TestVariableSleepTime $HOST_A $HOST_B $WAIT_TURBINES_TIME $isCentralized

  # Centralized tests #
  $isCentralized = $true

  TestVariableNumeberOfTurbines $HOST_A $HOST_B $WAIT_TURBINES_TIME $isCentralized
  #TestVariableSleepTime $HOST_A $HOST_B $WAIT_TURBINES_TIME $isCentralized
}

#Run the tests suite
runTests $HOST_A $HOST_B $WAIT_TURBINES_TIME

#$CMD = $("../putty.exe -ssh -pw end2endtest -t " + $HOST_A + """ cd " + $WORK_DIR + " && " + $DECENTRALICED_RUN_CMD + " " + $nTurbines + """")  


#$command = { get-eventlog -log "windows powershell" | where {$_.message -like "*certificate*"} }
#invoke-command -computername Server64, Server65, Server102 -scriptblock $command

