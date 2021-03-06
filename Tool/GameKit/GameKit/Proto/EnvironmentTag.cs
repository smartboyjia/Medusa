// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: EnvironmentTag.proto
// Note: requires additional types generated from: Geometry.proto
namespace Medusa.CoreProto
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"EnvironmentTag")]
  public partial class EnvironmentTag : global::ProtoBuf.IExtensible
  {
    public EnvironmentTag() {}
    
    private Medusa.CoreProto.EnvironmentTag.Versions _Version;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"Version", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public Medusa.CoreProto.EnvironmentTag.Versions Version
    {
      get { return _Version; }
      set { _Version = value; }
    }
    private Medusa.CoreProto.EnvironmentTag.Devices _Device;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"Device", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public Medusa.CoreProto.EnvironmentTag.Devices Device
    {
      get { return _Device; }
      set { _Device = value; }
    }
    private Medusa.CoreProto.EnvironmentTag.Languages _Language;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"Language", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public Medusa.CoreProto.EnvironmentTag.Languages Language
    {
      get { return _Language; }
      set { _Language = value; }
    }
    [global::ProtoBuf.ProtoContract(Name=@"Versions")]
    public enum Versions
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"main", Value=1)]
      main = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"free", Value=2)]
      free = 2
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"Devices")]
    public enum Devices
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"sd", Value=1)]
      sd = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"hd", Value=2)]
      hd = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"hd5", Value=4)]
      hd5 = 4,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ipad", Value=8)]
      ipad = 8,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ipad3", Value=16)]
      ipad3 = 16
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"Languages")]
    public enum Languages
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"enus", Value=1)]
      enus = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"zhcn", Value=2)]
      zhcn = 2
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}