
$gFileName = "C:\Web\HPPP_Controller\MemLog_$(get-date -f yyyyMMdd).csv"
$gAdapterName = "Wi-Fi" #Ethernet #Wi-Fi


if(Test-Path $gFileName){
    Remove-Item $gFileName
}
$i = 0

$OrigianlBytes = Get-NetAdapterStatistics -Name $gAdapterName | Select-Object SentBytes,ReceivedBytes
$Process = Get-Process DecentralizedParkPilot  | Select-Object -first 1

while($true){
    $i++
    $gDateTime = Get-Date -format "yyyy-MM-dd HH:mm:ss"
    $Network = Get-NetAdapterStatistics -Name $gAdapterName

    $recived = $Network.ReceivedBytes - $OrigianlBytes.ReceivedBytes
    $sent = $Network.SentBytes - $OrigianlBytes.SentBytes

    $Obj = New-Object psobject
    $Obj | Add-Member -MemberType NoteProperty -Name DateTime -Value $gDateTime
    #$Obj | Add-Member -MemberType NoteProperty -Name ID -Value $Process.Id
    $Obj | Add-Member -MemberType NoteProperty -Name Name -Value $Process.Name
    $Obj | Add-Member -MemberType NoteProperty -Name PagedMem -Value $Process.PagedMemorySize64
    $Obj | Add-Member -MemberType NoteProperty -Name PagedSysMem -Value $Process.PagedSystemMemorySize64
    $Obj | Add-Member -MemberType NoteProperty -Name nonPagedSystemMem -Value $Process.NonpagedSystemMemorySize64
    $Obj | Add-Member -MemberType NoteProperty -Name ReceivedBytes -Value $recived
    $Obj | Add-Member -MemberType NoteProperty -Name SentBytes -Value $sent
    #$Obj | Add-Member -MemberType NoteProperty -Name ReceivedBroadcastBytes -Value $Network.ReceivedBroadcastBytes
    #$Obj | Add-Member -MemberType NoteProperty -Name SentBroadcastBytes -Value $Network.SentBroadcastBytes
    #$Obj | Add-Member -MemberType NoteProperty -Name ReceivedMulticastBytes -Value $Network.ReceivedMulticastBytes
    #$Obj | Add-Member -MemberType NoteProperty -Name SentMulticastBytes -Value $Network.SentMulticastBytes
    #$Obj | Add-Member -MemberType NoteProperty -Name ReceivedUnicastBytes -Value $Network.ReceivedUnicastBytes
    #$Obj | Add-Member -MemberType NoteProperty -Name SentUnicastBytes -Value $Network.SentUnicastBytes
    $Obj | Export-Csv -Path $gFileName -Delimiter "," -Append -NoTypeInformation

    #    Write-Host $Obj.DateTime : $Obj.PagedMem
    if($i -eq 1){
        Write-Output $Obj | Format-Table -AutoSize
    }else{
        Write-Output $Obj | Format-Table -AutoSize -HideTableHeaders
    }

    if($i -gt 1000){
        break
    }

    Start-Sleep -m 100
    $Process.Refresh()

}
    
#This removes double quotes from the numeric columns (content of the regexp depends on the Add-Members above)
(Get-Content $gFileName) -replace '^"(.*?)",(.*?),"(.*?)",(.*?),"(.*?)","(.*?)","(.*?)",(.*?)$', '$1,$2,$3,$4,$5,$6,$7,$8' | Set-Content $gFileName