Remove-Item .\DiKErnel_src_*.zip
git archive --output ('.\DiKErnel_src_' + (get-date -Format yyyyMMdd) + '.zip') --prefix=DiKErnel_src/ HEAD: DiKErnel