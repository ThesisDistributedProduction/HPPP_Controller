

$HOST_A = "stefan@192.168.0.100"
$HOST_B = "theis@192.168.0.101"

$WORK_DIR = "~/work/HPPP_Controller/ScriptsHelper"
$DECENTRALICED_RUN_CMD = "bash -l ./runXDecentralized.sh"

$SAMPLE_TIME = 120
$WAIT_TURBINES_TIME = 0 #NEEDS CALIBRATION

Function StartRemoteTurbine{
  Param ([string]$HOST_SYSTEM = 0, [int]$nTurbines = 0, [int]$mSleep = 20)
  $remoteCmd = """cd ~/work/HPPP_Controller&& bash -l ./runXDecentralized.sh $nTurbines $mSleep"""
  $CMD = [scriptblock]::Create("..\Tools\putty.exe -ssh -pw end2endtest -t $HOST_SYSTEM $remoteCmd")
#  Invoke-Command -scriptblock $CMD

  Write-Host $CMD
}

Function KilleRemoteTurbines{
  Param ()
  $remoteCmd = """killall -9 DecentralizedParkPilot"""
  $CMD = [scriptblock]::Create("..\Tools\putty.exe -ssh -pw end2endtest -t $HOST_SYSTEM $remoteCmd")
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
  
  StartRemoteTurbine $HOST_A $nTurbinesA
  StartRemoteTurbine $HOST_B $nTurbinesB
  OpenMatlab

  sleep $WAIT_TURBINES_TIME
}


#$CMD = $("../putty.exe -ssh -pw end2endtest -t " + $HOST_A + """ cd " + $WORK_DIR + " && " + $DECENTRALICED_RUN_CMD + " " + $nTurbines + """")  


#$command = { get-eventlog -log "windows powershell" | where {$_.message -like "*certificate*"} }
#invoke-command -computername Server64, Server65, Server102 -scriptblock $command

