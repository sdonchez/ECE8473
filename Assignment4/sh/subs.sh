# decrypt substitution cipher

  in="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
subs="MVB2TE7ZA4X90Q51FCU8ILYDSGJ3HK6PRONW" # for alice

# tr "$in" "$subs" # encrypt

tr "$subs" "$in" # decrypt

