local Utils = {}

function Utils.safeRequire(module, defaultModule)
    local status, lib = pcall(require, module)
    if (status) then
        return lib
    else
        return require(defaultModule)
    end
end

return Utils
