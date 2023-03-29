Pod::Spec.new do |s|
  s.name         = 'Taplytics_tvOS'
  s.version      = '4.2.1'
  s.author       = { 'Taplytics' => 'help@taplytics.com' }
  s.license      = { :type => 'Commercial', :text => 'See https://taplytics.com/terms' }
  s.homepage     = 'https://taplytics.com'
  s.summary      = 'tvOS framework for using the Taplytics native mobile A/B testing service.'
  s.description  = 'For installation instructions, please visit: https://github.com/taplytics/taplytics-ios-sdk'
  s.source = { :git => 'https://github.com/taplytics/taplytics-ios-sdk.git', :tag => "#{s.version}" }
  s.platform = :tvos, '11.0'
  s.frameworks = 'SystemConfiguration', 'JavaScriptCore'
  s.vendored_frameworks = "Taplytics_tvOS.xcframework"
end
